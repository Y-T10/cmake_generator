#include "AppCGenProject.hpp"

#include <string>
#include "CmpRenderRendering.hpp"

using namespace cxxopts;
using namespace inja;
using namespace std;

namespace {
const json CreateProjectParam(const ParseResult& result) noexcept {
    const auto policies = json::array({
        json::object({{"number", "0076"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0128"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0074"}, {"value", "NEW"}, {"isGlobal", true}}),
        json::object({{"number", "0077"}, {"value", "NEW"}, {"isGlobal", true}})
    });
    const auto projectProps = json::object({
        {"name", result["name"].as<string>()},
        {"version", result["ver"].as<string>()},
        {"lang", result["lang"].as<string>()},
        {"buildType", result["bt"].as<string>()},
        {"policies", policies}
    });
    return projectProps;
};
}

namespace AppCGen {
void OptionProj(Options& opt) noexcept {
    opt.add_options("project")
        ("root", "specify root project with CMake version", value<string>()->default_value(""))
        ("ver", "project version", value<string>()->default_value("0.0.0"))
        ("lang", "project programming language", value<string>()->default_value("CXX"))
        ("bt", "project default build type", value<string>()->default_value("Release"));
}

const std::optional<inja::json>ArgParseProj(const ParseResult& result) noexcept{
    if(result.count("root") == 0){
        return nullopt;
    }

    return json::object({
        {"cmakeVersionMin", result["root"].as<string>()},
        {"project", CreateProjectParam(result)}
    });
}

void LoadTplProj(const inja::json& prop, std::ostream& out) noexcept{
    CompRender::RenderText(out, "project", prop);
}
};