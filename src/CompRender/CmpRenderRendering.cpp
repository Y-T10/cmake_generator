#include "CmpRenderRendering.hpp"

#include <filesystem>
#include <ostream>
#include <cstdlib>
#include "fmt/format.h"

using namespace std::filesystem;
using namespace inja;
using namespace fmt;

namespace {
    const Environment CreateCustomEnv() noexcept {
        Environment env;
        env.set_lstrip_blocks(true);
        env.set_trim_blocks(true);
        return env;
    };
}

namespace CompRender {
std::ostream& RenderText(std::ostream& out, const std::filesystem::path& tplFilePath, const inja::json& props) noexcept {
    auto env = CreateCustomEnv();
    if(tplFilePath.empty()){
        return out;
    }

    const auto tpl =  env.parse_template(tplFilePath.generic_string());
    return env.render_to(out, tpl, props);
}

    const std::filesystem::path AppendTemplateFileExt(const std::string& filename) noexcept{
        return format(FMT_STRING("{:s}.jinja"), filename);
    }
};