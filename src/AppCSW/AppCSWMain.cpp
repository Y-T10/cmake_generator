#include "CmpRenderRendering.hpp"

#include <algorithm>
#include <iostream>
#include "fmt/format.h"
#include "cxxopts.hpp"
#include "CmpCGAddSubDirs.hpp"
#include "CmpCGProject.hpp"
#include "CmpCGLibrary.hpp"
#include "CmpCGBinary.hpp"
#include "AppBuildConf.hpp"
#include <filesystem>
#include <functional>
#include <optional>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>
#include "CmpFileSysPath.hpp"

#include "AppCSWTemplate.hpp"

using namespace std;
using namespace inja;
using namespace cxxopts;
using namespace std::filesystem;
using namespace std::string_literals;
using namespace fmt;

/**
 * @brief ヘルプを出力する
 * @param opt オプションオブジェクト
 * @param dashOptFmt ダッシュ付き引数の書式
 * @param spaceOptsFmt ダッシュなし引数の書式
 */
void PrintHelp(const Options& opt, const string& dashOptFmt = "", const string& spaceOptsFmt = "") noexcept {
    Options helpOpt = opt;
    helpOpt.custom_help(dashOptFmt);
    helpOpt.positional_help(spaceOptsFmt);

    print(FMT_STRING("{:s}"), helpOpt.help());
}

inline void PrintError(const std::string& error) noexcept{
    print(stderr, FMT_STRING("{:s}: {:s}\n"), AppCSWConf::ProgramName(), error);
}

// 予期せぬ引数に対するエラーを出力する
void PrintUmmatchedError(const ParseResult& result) noexcept {
    const auto unmatchedList = accumulate(
        result.unmatched().begin(), result.unmatched().end(),
        string(""), [](const string& l, const string& r){
            return format(FMT_STRING("{:s}\"{:s}\" "), l, r);
        });
    print(stderr, FMT_STRING("{:s}: unrecognized parameter(s) -- {:s}\n"), AppCSWConf::ProgramName(), unmatchedList);
    print(stderr, FMT_STRING("Try \'{:s} --help\' for more information.\n"), AppCSWConf::ProgramName(), unmatchedList);
}

Options CreateAppArgParser(const string& desc) noexcept {
    const auto proName = string(AppCSWConf::ProgramName());
    Options opt(proName, format(FMT_STRING("{:s}: {:s}"), proName, desc));
    opt.allow_unrecognised_options();
    opt.add_options()
        ("h,help", "print this help")
        ("t,type", "type of code generated", value<string>()->default_value("none")->no_implicit_value())
        ("n,name", "project/library/binary name", value<string>())
        ("I,templatePath", "search path for template files", value<vector<string>>()->default_value({}))
        ("output-dir", "directory where CMake files are output", value<string>())
        ("verbose", "enable verbose output");
    opt.parse_positional({"output-dir"});
    CmpCG::OptionProj(opt);
    CmpCG::OptionLib(opt);
    return opt;
}

const bool DoGenerate(
const function<const optional<json>(const ParseResult&)>& opt2prop,
const function<const std::filesystem::path(const ParseResult&)>& tplFilePath,
const ParseResult& result, ostream& out) noexcept{
    assert(opt2prop);
    assert(tplFilePath);
    const auto prop = opt2prop(result);
    if(!prop){
        PrintError("creating template properties failed.");
        return false;
    }

    const auto fileName = tplFilePath(result);
    auto templateDirs = DefaultTemplateDirs("templates");
    std::ranges::copy(
        CmpFile::ConvertToPaht(result["templatePath"].as<vector<string>>()),
        std::back_inserter(templateDirs)
    );

    const auto filePath = SearchTemplateFile(templateDirs, fileName.string());
    if(filePath.empty()){
        PrintError(fmt::format("template file \"{:s}\" not found.", fileName.string()));
        return false;
    }
    CompRender::RenderText(out, filePath, *prop);
    out << std::endl;
    return true;
}

const bool GenerateCode(const ParseResult& result, ostream& out) noexcept {
    const auto codeType = result["type"].as<string>();
    if(codeType == "project" || codeType == "proj") {
        return DoGenerate(CmpCG::ArgParseProj, CmpCG::TplPathProj, result, out);
    }else if(codeType == "library" || codeType == "lib") {
        return DoGenerate(CmpCG::ArgParseLib, CmpCG::TplPathLib, result, out);
    }else if(codeType == "binary" || codeType == "bin") {
        return DoGenerate(CmpCG::ArgParseBin, CmpCG::TplPathBin, result, out);
    }else if(codeType == "none") {
        return true;
    }

    print(stderr, FMT_STRING("{:s}: unknwon code type \"{:s}\".\n"), "tcm", codeType);
    return false;
}

const bool CheckArguments(const ParseResult& result) noexcept {
    if(!result.unmatched().empty()) {
        PrintUmmatchedError(result);
        return false;
    }

    if(result.count("output-dir") == 0){
        PrintError("no output direcotry is specified.");
        return false;
    }

    const auto outputDir = std::filesystem::path(result["output-dir"].as<string>());
    if(!exists(outputDir)){
        PrintError(fmt::format(FMT_STRING("{} does not exist."), outputDir.string()));
        return false;
    }
    if(!is_directory(outputDir)){
        PrintError(fmt::format(FMT_STRING("{} is not directory."), outputDir.string()));
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    auto opt = CreateAppArgParser("Generat CMake code depending on options.");
    const auto result = opt.parse(argc, argv);

    if(!!result.count("help") || result.arguments().empty()){
        PrintHelp(opt, "[options]", "</path/to/output/direcotry>");
        return 0;
    }

    if(!CheckArguments(result)){
        return 1;
    }

    const auto outputDir = CmpFile::ResolvePath(std::filesystem::path(result["output-dir"].as<string>()));
    if(outputDir.empty()) {
        PrintError(format(FMT_STRING("failed resolving a output path.")));
        return 1;
    }
    std::ofstream outputFile(outputDir / "CMakeLists.txt");

    if(!GenerateCode(result, outputFile)){
        return 1;
    }

    if(!DoGenerate(CmpCG::ArgParseAddSubdir, CmpCG::TplPathAddSubdir, result, outputFile)){
        return 1;
    }

    return 0;
};