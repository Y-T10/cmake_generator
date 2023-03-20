#include "CmpCGLibrary.hpp"

#include <algorithm>
#include <string>
#include "CmpRenderRendering.hpp"
#include "CmpCGUtility.hpp"
#include <filesystem>
#include <vector>

using namespace std::filesystem;
using namespace cxxopts;
using namespace inja;
using namespace std;

namespace {
const json CreateTargetParam(const ParseResult& result) noexcept {
    const auto sourceFiles = CmpCGUtil::ListFilesInDir(
        result["output-dir"].as<string>(),
        regex(R"(^[\w\-\.]+\.(c\+\+|cxx|cc|cpp)$)")
    );
    if(!sourceFiles.has_value()){
        return {};
    }

    return json::object({
        {"name", CmpCGUtil::GetName(result)},
        {"properties", json::array({})},
        {"sources", *sourceFiles},
        {"includeDirs", json::array({"${CMAKE_CURRENT_SOURCE_DIR}"})},
        {"libraries", CmpCGUtil::toJSON(result["lib"].as<std::vector<string>>())}
    });
};
}

namespace CmpCG {
void OptionLib(Options& opt) noexcept {
    opt.add_options("library")
        ("lib", "depending libray name in CMake", value<std::vector<string>>()->default_value({}));
}

const std::optional<inja::json>ArgParseLib(const ParseResult& result) noexcept{
    const auto libProps = CreateTargetParam(result);
    if(libProps.empty()){
        return nullopt;
    }

    return json::object({
        {"target", libProps}
    });
}

void LoadTplLib(const inja::json& prop, const ParseResult& result, std::ostream& out) noexcept{
    const auto addiPaths = CmpCGUtil::ConvertToPaht(result["I"].as<vector<string>>());
    CompRender::RenderText(out, "library", prop, addiPaths);
}
};