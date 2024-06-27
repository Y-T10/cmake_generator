#include "CmpCGLibrary.hpp"

#include <string>
#include "CmpRenderRendering.hpp"
#include "CmpCGTarget.hpp"
#include <filesystem>
#include <vector>

using namespace std::filesystem;
using namespace cxxopts;
using namespace inja;
using namespace std;

namespace CmpCG {
void OptionLib(Options& opt) noexcept {
    opt.add_options("library")
        ("lib", "depending libray name in CMake", value<std::vector<string>>()->default_value({}));
}

const std::optional<inja::json>ArgParseLib(const ParseResult& result) noexcept{
    const auto libProps = CmpCGTarget::CreateTargetParam(result);
    if(libProps.empty()){
        return nullopt;
    }

    return json::object({
        {"target", libProps}
    });
}

const std::filesystem::path TplPathLib(const cxxopts::ParseResult& result) noexcept{
    return CompRender::AppendTemplateFileExt("library");
}
};