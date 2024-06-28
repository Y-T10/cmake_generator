#include "AppCSWTemplate.hpp"

#include "CmpConfInstall.hpp"
#include <algorithm>
#include <filesystem>

/**
 * @brief デフォルトのテンプレートディレクトリの一覧を返す
 * @return ディレクトリパスの配列
 */
const std::vector<std::filesystem::path> DefaultTemplateDirs(const std::string& direcotryName) noexcept {
    return {
        {std::filesystem::current_path() / direcotryName},
        {CmpConf::InstallDataPath() / direcotryName}
    };
}

const std::filesystem::path SearchTemplateFile(const std::vector<std::filesystem::path>& direcotries,const std::string& filename) noexcept {
    if (filename.empty()) {
        return "";
    }

    const auto ContainingDir = std::ranges::find_if(direcotries, [&filename](const std::filesystem::path& dir){
        return std::filesystem::exists(dir / filename);
    });

    if (ContainingDir == direcotries.end()) {
        return "";
    }
    return (*ContainingDir) / filename;
}