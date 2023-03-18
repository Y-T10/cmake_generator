#include "AppCGenLibrary.hpp"

#include <algorithm>
#include <string>
#include "CmpRenderRendering.hpp"
#include "AppCGListFiles.hpp"

using namespace cxxopts;
using namespace inja;
using namespace std;

namespace {
const json toJSON(const std::vector<string>& strings){
    auto dst = json::array({});
    std::transform(strings.begin(), strings.end(), std::back_inserter(dst), [](const string& str)->const json{
        return json(str);
    });
    return dst;
}

const json CreateTargetParam(const ParseResult& result) noexcept {
    const auto sourceFiles = AppCGListFiles::ListFilesInDir(
        std::filesystem::current_path(),
        regex(R"(^[\w\-\.]+\.(c\+\+|cxx|cc|cpp)$)")
    );
    if(!sourceFiles.has_value()){
        return {};
    }

    return json::object({
        {"name", result["name"].as<string>()},
        {"properties", json::array({})},
        {"sources", *sourceFiles},
        {"includeDirs", json::array({"${CMAKE_CURRENT_SOURCE_DIR}"})},
        {"libraries", toJSON(result["lib"].as<std::vector<string>>())}
    });
};
}

namespace AppCGen {
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

void LoadTplLib(const inja::json& prop, std::ostream& out) noexcept{
    CompRender::RenderText(out, "library", prop);
}
};