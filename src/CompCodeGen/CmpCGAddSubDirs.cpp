#include "CmpCGAddSubDirs.hpp"

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
    void GenerateAddSubdir(const std::filesystem::path& dir, const cxxopts::ParseResult& result, std::ostream& out) noexcept {
        const auto subDirsProps = json::object({
            {"subDirs", ListSubDirs(dir, [](const path& subDir) -> bool{return exists(subDir / "CMakeLists.txt");})}
        });
        if(subDirsProps.empty()){
            return;
        }

        const auto addiPaths = CmpCGUtil::ConvertToPaht(result["I"].as<vector<string>>());
        CompRender::RenderText(out, "addSubDirectories", subDirsProps, addiPaths);
        out << std::endl;
    }
}