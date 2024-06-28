#include "CmpCGAddSubDirs.hpp"

#include <string>
#include "CmpRenderRendering.hpp"
#include <filesystem>
#include <vector>

using namespace std::filesystem;
using namespace cxxopts;
using namespace inja;
using namespace std;

namespace {
    const vector<path> GetSubDirs(const path& dir) noexcept {
        if(!is_directory(dir)){
            return {};
        }

        vector<path> subDirs = {};
        for (const directory_entry& e : directory_iterator(dir, directory_options::skip_permission_denied)) {
            if(!e.is_directory()){
                continue;
            }
            subDirs.emplace_back(e.path());
        }
        return subDirs;
    };

    const json::array_t  ListSubDirs(const path& dir, const std::function<bool(const path&)>& cond) noexcept {
        json::array_t targetDirs = {};
        for(const auto& sub: GetSubDirs(dir)){
            if(cond(sub)){
                targetDirs.emplace_back(sub.stem().string());
            }
        }

        return targetDirs;
    }
}

namespace CmpCG {
    const optional<json> ArgParseAddSubdir(const ParseResult& result) noexcept {
        assert(result["output-dir"].count());
        const auto outputDir = path(result["output-dir"].as<string>());

        const auto subDirs = ListSubDirs(outputDir, [](const path& subDir) -> bool{
            return exists(subDir / "CMakeLists.txt");
        });

        return json::object({
            {"subDirs", subDirs}
        });
    }

    const path TplPathAddSubdir(const cxxopts::ParseResult& result) noexcept {
        return CompRender::AppendTemplateFileExt("addSubDirectories");
    }
}