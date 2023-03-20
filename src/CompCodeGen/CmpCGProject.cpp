#include "CmpCGProject.hpp"

#include <string>
#include "CmpRenderRendering.hpp"
#include "CmpCGUtility.hpp"
#include "CmpConfCMake.hpp"

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

namespace CmpCG {
void OptionProj(Options& opt) noexcept {
    const string defCMakeVer = string(CmpConf::DefaultCMakeVersion());
    opt.add_options("project")
        ("root", "specify root project with CMake version", value<string>()->default_value(defCMakeVer))
        ("ver", "project version", value<string>()->default_value("0.0.0"))
        ("lang", "project programming language", value<string>()->default_value("CXX"))
        ("bt", "project default build type", value<string>()->default_value("Release"));
}

const std::optional<inja::json>ArgParseProj(const ParseResult& result) noexcept{
    return json::object({
        {"cmakeVersionMin", result["root"].as<string>()},
        {"project", CreateProjectParam(result)}
    });
}

void LoadTplProj(const inja::json& prop, const ParseResult& result, std::ostream& out) noexcept{
    const auto addiPaths = CmpCGUtil::ConvertToPaht(result["I"].as<vector<string>>());
    CompRender::RenderText(out, "project", prop, addiPaths);
}
};