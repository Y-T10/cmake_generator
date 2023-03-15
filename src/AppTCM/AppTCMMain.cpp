#include "CmpRenderRendering.hpp"

#include <iostream>
#include <cstdint>
#include "fmt/format.h"
#include "cxxopts.hpp"
#include "AppTCMOptions.hpp"
#include <filesystem>
#include <cassert>
#include <numeric>

using namespace std;
using namespace inja;
using namespace cxxopts;
using namespace std::filesystem;
using namespace std::string_literals;

// セマンティックバージョンを表す型
struct Version {
    uint8_t major = 0;
    uint8_t minor = 0;
    uint8_t patch = 0;
};

// バージョンを文字列に変える関数
const std::string toString(const Version& v) noexcept {
    return fmt::format("{:d}.{:d}.{:d}", v.major, v.minor, v.patch);
}

// projectのパラメータ
const json CreateProjectParam(const string& name, const Version& version, const string& lang, const string& buildType) noexcept {
    const auto policies = json::array({
        json::object({{"number", "0076"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0128"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0074"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0077"}, {"value", "NEW"}, {"isGlobal", true}})
    });
    const auto projectProps = json::object({
        {"name", name},
        {"version", toString(version)},
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

    fmt::print(FMT_STRING("{:s}"), helpOpt.help());
}

Options CreateAppArgParser(const string& programName, const string& desc) noexcept {
    Options opt(programName, desc);
    opt.allow_unrecognised_options();
    opt.show_positional_help();
    opt.add_options()
        ("h,help", "print this help")
        ("type", "a type of code generated");
    opt.parse_positional({"<type>"});
    return opt;
}

int main(int argc, char* argv[]) {
    auto opt = CreateAppArgParser(
        (argv[0]==nullptr)? "tcm": path(argv[0]).filename(),
        "Generat CMake code depending on options.");
    const auto result = opt.parse(argc, argv);

    if(!result.unmatched().empty()) {
        const auto unmatchedList = accumulate(
            result.unmatched().begin(), result.unmatched().end(),
            string(""), [](const string& l, const string& r){ return  l + r + " "s;});
        fmt::print(stderr, "{:s}: unrecognized parameter -- {:s}", opt.program(), unmatchedList);
        fmt::print(stderr, "Try \'{:s} --help\' for more information.", opt.program(), unmatchedList);
        return 1;
    }

    if(result.count("help") || result.arguments().empty()){
        PrintHelp(opt, "[-h/--help]", "<type> [<args>]");
        return 0;
    }

    CompRender::RenderText(std::cout, "project.tpl", json::object({
        {"cmakeVersionMin", toString({0,0,0})},
        {"project", CreateProjectParam("", {0,0,0}, "CXX", "Release")}
    }));
    return 0;
};