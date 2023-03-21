#include "CmpRenderRendering.hpp"

#include <iostream>
#include <cstdint>
#include "fmt/format.h"
#include "fmt/std.h"
#include "cxxopts.hpp"
#include "CmpCGAddSubDirs.hpp"
#include "CmpVerVersion.hpp"
#include "CmpCGProject.hpp"
#include "CmpCGLibrary.hpp"
#include "AppBuildConf.hpp"
#include <filesystem>
#include <functional>
#include <optional>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>
#include "CmpConfInstall.hpp"
#include "CmpFileSysPath.hpp"

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
    print(stderr, FMT_STRING("{:s}: {:s}\n"), AppTCMConf::ProgramName(), error);
}

// 予期せぬ引数に対するエラーを出力する
void PrintUmmatchedError(const ParseResult& result, const string& programName) noexcept {
    const auto unmatchedList = accumulate(
        result.unmatched().begin(), result.unmatched().end(),
        string(""), [](const string& l, const string& r){
            return format(FMT_STRING("{:s}\"{:s}\" "), l, r);
        });
    print(stderr, FMT_STRING("{:s}: unrecognized parameter(s) -- {:s}\n"), programName, unmatchedList);
    print(stderr, FMT_STRING("Try \'{:s} --help\' for more information.\n"), programName, unmatchedList);
}

Options CreateAppArgParser(const string& programName, const string& desc) noexcept {
    Options opt(programName, format(FMT_STRING("{:s}: {:s}"), programName, desc));
    opt.allow_unrecognised_options();
    opt.add_options()
        ("h,help", "print this help")
        ("t,type", "type of code generated", value<string>()->default_value("none")->no_implicit_value())
        ("n,name", "project/library/binary name", value<string>())
        ("I,templatePath", "search path for template files", value<vector<string>>()->default_value({}))
        ("output-dir", "directory where CMake files are output", value<string>());
    opt.parse_positional({"output-dir"});
    CmpCG::OptionProj(opt);
    CmpCG::OptionLib(opt);
    return opt;
}

const vector<path> CreateDefaultPaths() noexcept{
    const auto homeDir = CmpFile::HomeDir();
    return vector<path>{
        current_path() / ".tpl",
        homeDir.empty()? "": homeDir / format(".{:s}", AppTCMConf::ProgramName()) / "template",
        CmpConf::InstallDataPath() / "template"
    };
}

const vector<path> CreateSearchPaths(const ParseResult& result) noexcept {
    auto searchPaths = CmpFile::ConvertToPaht(result["templatePath"].as<vector<string>>());
    for(const auto& path: CreateDefaultPaths()){
        searchPaths.emplace_back(path);
    }
    return searchPaths;
}

const path SearchTplFile(const path& tplFilePath, const vector<path>& searchPath) noexcept {
    if(tplFilePath.is_absolute()){
        return exists(tplFilePath)? tplFilePath: "";
    }

    assert(tplFilePath.is_relative());
    for(const auto& dir: searchPath){
        if(exists(dir / tplFilePath)){
            return dir / tplFilePath;
        }
    }
    return "";
};

const bool DoGenerate(
const function<const optional<json>(const ParseResult&)>& opt2prop,
const function<void(const json&, const ParseResult&, ostream&)>& codeGenerator,
const ParseResult& result, ostream& out) noexcept{
    assert(opt2prop);
    assert(codeGenerator);
    const auto prop = opt2prop(result);
    if(!prop){
        PrintError("creating template properties failed.");
        return false;
    }
    codeGenerator(*prop, resutl, out);
    // GenerateAddSubdir();
    return true;
}

const bool GenerateCode(const ParseResult& result, ostream& out) noexcept {
    const auto codeType = result["type"].as<string>();
    if(codeType == "project" || codeType == "proj") {
        return DoGenerate(CmpCG::ArgParseProj, CmpCG::LoadTplProj, result, out);
    }else if(codeType == "library" || codeType == "lib") {
        return DoGenerate(CmpCG::ArgParseLib, CmpCG::LoadTplLib, result, out);
    }else if(codeType == "binary" || codeType == "bin") {
        // DoGenerate(ArgParseBin, LoadTplBin, resutl);
    }else if(codeType == "none") {
        const auto noneProp = [](const ParseResult& result) -> optional<json>{
            return json();
        };
        const auto noneCG = [](const json& prop, const ParseResult& result, ostream& out){
            return;
        };
        return DoGenerate(noneProp, noneCG, result, out);
    }

    print(stderr, FMT_STRING("{:s}: unknwon code type \"{:s}\".\n"), "tcm", codeType);
    return false;
}

int main(int argc, char* argv[]) {
    auto opt = CreateAppArgParser(string(AppTCMConf::ProgramName()),
        "Generat CMake code depending on options.");
    const auto result = opt.parse(argc, argv);

    if(!result.unmatched().empty()) {
        PrintUmmatchedError(result, opt.program());
        return 1;
    }

    if(!!result.count("help") || result.arguments().empty()){
        PrintHelp(opt, "[options]", "</path/to/output/direcotry>");
        return 0;
    }

    if(result.count("output-dir") == 0){
        PrintError("no output direcotry is specified.");
        return 2;
    }

    const auto outputDir = path(result["output-dir"].as<string>());
    if(!exists(outputDir)){
        PrintError(format(FMT_STRING("{} does not exist."), outputDir));
        return 2;
    }
    if(!is_directory(outputDir)){
        PrintError(format(FMT_STRING("{} is not directory."), outputDir));
        return 2;
    }
    std::ofstream outputFile(outputDir / "CMakeLists.txt");

    if(!GenerateCode(result, outputFile)){
        return 1;
    }
    CmpCG::GenerateAddSubdir(outputDir, result, outputFile);

    return 0;
};