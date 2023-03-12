#include "CmpRenderRendering.hpp"

#include <filesystem>
#include <optional>
#include <ostream>

using namespace std::filesystem;
using namespace inja;

namespace CompRender {
std::ostream& RenderText(std::ostream& out, const  std::string& templateName, const json& props) noexcept {
    Environment env;
    const auto tpl =  env.parse_template(current_path() / "template" / templateName);
    return env.render_to(out, tpl, props);
}
};