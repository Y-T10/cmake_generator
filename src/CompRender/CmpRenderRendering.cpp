#include "CmpRenderRendering.hpp"

#include "jinja2cpp/template_env.h"
#include <optional>
#include <ostream>

using namespace jinja2;
using namespace std::filesystem;

namespace {
void LogResult(const Result<void>& result) noexcept {
    // TODO: ここを実装
};
const bool CheckResut(const Result<void>& result) noexcept {
    if(result){
        return true;
    }
    LogResult(result);
    return false;
}
std::optional<Template> CreaateRenderer(const path& path) noexcept {
    if(!exists(path)){
        return std::nullopt;
    }
    Template renderer;
    if(CheckResut(renderer.LoadFromFile(path.string()))) {
        // TODO: エラーを表示する
        return std::nullopt;
    }
    return renderer;
};
}

namespace CompRender {
std::ostream& RenderText(std::ostream& out, const  std::filesystem::path& path, const ValuesMap& props) noexcept {
    auto renderer = CreaateRenderer(path);
    if(!renderer) {
        return out;
    }
    LogResult(renderer->Render(out, props));
    return out;
}
};