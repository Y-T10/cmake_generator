#include "CmpRenderRendering.hpp"

#include <iostream>
#include <cstdint>
#include "fmt/format.h"
#include "AppMainOptions.hpp"
#include <filesystem>
#include <cassert>

using namespace std;
using namespace inja;
using namespace std::filesystem;

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

// main関数のパラメータをパースする
const AppMain::AppOption ParseAppArgs(const int argc, const char* argv[]) noexcept {
    assert(argc >= 0);
    const string programName = (argc > 0)? "tcm": path(argv[0]).filename().string();
    const int paramArgc = (argc > 0)? argc - 1: 0;
    const char** paramArgv = (argc > 0)? (argv + 1): argv;
    assert(paramArgv[paramArgc] == nullptr);
    return AppMain::ParseOptions(programName, "テンプレートファイルからCMakeファイルを生成する．", paramArgc, paramArgv);
};

const cxxopts::Options CreateAppArgParser(const int argc, const char* argv[]) noexcept {
    
}

int main(int argc, char* argv[]) {
    const auto opt = ParseOptions();
    const auto args = ParseAppArgs(argc, argv);

    if(args.count("h")){
    }

    CompRender::RenderText(std::cout, "project.tpl", json::object({
        {"cmakeVersionMin", toString({0,0,0})},
        {"project", CreateProjectParam("", {0,0,0}, "CXX", "Release")}
    }));
    return 0;
};