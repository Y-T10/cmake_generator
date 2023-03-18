#include "CmpRenderRendering.hpp"

#include <iostream>
#include <cstdint>
#include "fmt/format.h"
#include "cxxopts.hpp"
#include "AppTCMOptions.hpp"
#include "CmpVerVersion.hpp"
#include "AppCGenProject.hpp"
#include "AppCGenLibrary.hpp"
#include <filesystem>
#include <functional>
#include <optional>
#include <cassert>
#include <numeric>
#include <string>

using namespace std;
using namespace inja;
using namespace cxxopts;
using namespace std::filesystem;
using namespace std::string_literals;
using namespace fmt;

// projectのパラメータ
const json CreateProjectParam(const string& name, const CmpVer::Version& version, const string& lang, const string& buildType) noexcept {
    const auto policies = json::array({
        json::object({{"number", "0076"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0128"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0074"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0077"}, {"value", "NEW"}, {"isGlobal", true}})
    });
    const auto projectProps = json::object({
        {"name", name},
        {"version", CmpVer::toString(version)},
        {"lang", lang},
        {"policies", policies},
        {"buildType", buildType}
    });
    return projectProps;
};

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
        ("t,type", "type of code generated", value<string>()->default_value(""))
        ("n,name", "project/library/binary name", value<string>()->default_value(""));
    AppCGen::OptionProj(opt);
    AppCGen::OptionLib(opt);
    return opt;
}

void DoGenerate(
const function<const optional<json>(const ParseResult&)>& opt2prop,
const function<void(const json&, ostream&)>& codeGenerator,
const ParseResult& resutl, ostream& out) noexcept{
    assert(opt2prop);
    assert(codeGenerator);
    const auto prop = opt2prop(resutl);
    if(!prop){
        return;
    }
    codeGenerator(*prop, out);
}

const bool GenerateCode(const ParseResult& result, ostream& out) noexcept {
    const auto codeType = result["type"].as<string>();
    if(codeType == "project" || codeType == "proj") {
        DoGenerate(AppCGen::ArgParseProj, AppCGen::LoadTplProj, result, out);
    }else if(codeType == "library" || codeType == "lib") {
        DoGenerate(AppCGen::ArgParseLib, AppCGen::LoadTplLib, result, out);
    }else if(codeType == "binary" || codeType == "bin") {
        // DoGenerate(ArgParseBin, LoadTplBin, resutl);
    }

    // GenerateAddSubdir();
    return true;
}

int main(int argc, char* argv[]) {
    auto opt = CreateAppArgParser(
        (argv[0]==nullptr)? "tcm": path(argv[0]).filename(),
        "Generat CMake code depending on options.");
    const auto result = opt.parse(argc, argv);

    if(!result.unmatched().empty()) {
        PrintUmmatchedError(result, opt.program());
        return 1;
    }

    if(!!result.count("help") || result.arguments().empty()){
        PrintHelp(opt, "[options]", "");
        return 0;
    }

    if(!GenerateCode(result, cout)){
        print(stderr, FMT_STRING("{:s}: code generation failed.\n"), opt.program());
        return 1;
    }

    return 0;
};