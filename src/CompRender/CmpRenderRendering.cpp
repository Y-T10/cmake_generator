#include "CmpRenderRendering.hpp"

#include <filesystem>
#include <optional>
#include <ostream>

using namespace std::filesystem;
using namespace inja;

namespace {
    const Environment CreateCustomEnv() noexcept {
        Environment env;
        env.set_lstrip_blocks(true);
        env.set_trim_blocks(true);
        return env;
    };
}

namespace CompRender {
std::ostream& RenderText(std::ostream& out, const  std::string& templateName, const json& props) noexcept {
    auto env = CreateCustomEnv();
    const auto tpl =  env.parse_template(current_path() / "template" / templateName);
    return env.render_to(out, tpl, props);
}
};