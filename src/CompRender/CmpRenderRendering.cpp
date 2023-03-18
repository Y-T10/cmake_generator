#include "CmpRenderRendering.hpp"

#include <filesystem>
#include <optional>
#include <ostream>
#include <cstdlib>
#include "fmt/format.h"

using namespace std::filesystem;
using namespace inja;

namespace {
const path HomeDir() noexcept {
    const char* homeDir = getenv("HOME");
    if(homeDir == nullptr){
        return "";
    }
    return path(homeDir);
}

const path SearchTplFile(const path& dir, const std::string& templateName) noexcept {
    for (const directory_entry& file : directory_iterator(dir)) {
        if(!file.is_regular_file()){
            continue;
        }
        if(file.path().extension() != "tpl"){
            continue;
        }
        if(file.path().stem() != templateName){
            continue;
        }
        return file.path();
    }
    return "";
}

const path FindTemplateFile(const std::string& templateName, const path& additionalDir) noexcept {
    const std::vector<path> searchList = {
        additionalDir,
        current_path() / ".tpl",
        HomeDir() / ".tcm" / "tpl",
        "${INSTALL_PREFIX}/share/tcm/template"
    };

    for(const auto& dir: searchList) {
        const auto file = SearchTplFile(dir, templateName);
        if(!file.empty()){
            return file;
        }
    }
    return "";
};
    const Environment CreateCustomEnv() noexcept {
        Environment env;
        env.set_lstrip_blocks(true);
        env.set_trim_blocks(true);
        return env;
    };
}

namespace CompRender {
std::ostream& RenderText(
std::ostream& out,
const std::string& templateName,
const json& props,
const path& additionalSearchDir) noexcept {
    auto env = CreateCustomEnv();

    const auto templateFile = FindTemplateFile(templateName, additionalSearchDir);
    if(templateFile.empty()){
        return out;
    }

    const auto tpl =  env.parse_template(templateFile);
    return env.render_to(out, tpl, props);
}
};