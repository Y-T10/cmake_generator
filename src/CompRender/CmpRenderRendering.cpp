#include "CmpRenderRendering.hpp"

#include <optional>
#include <ostream>

using namespace std::filesystem;
using namespace inja;

namespace CompRender {
std::ostream& RenderText(std::ostream& out, const  std::filesystem::path& path, const json& props) noexcept {
    if(!exists(path)){
        return out;
    }

    Environment env;
    Template renderer = env.parse_template(path.string());
    return env.render_to(out, renderer, props);;
}
};