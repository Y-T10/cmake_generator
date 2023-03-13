#include "CmpRenderRendering.hpp"

#include <iostream>
#include <cstdint>
#include "fmt/format.h"

using namespace std;
using namespace inja;

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

int main(int argc, char* argv[]) {
    CompRender::RenderText(std::cout, "project.tpl", json::object({
        {"cmakeVersionMin", toString({0,0,0})},
        {"project", CreateProjectParam("", {0,0,0}, "CXX", "Release")}
    }));
    return 0;
};