#pragma once

#include <filesystem>
#include <optional>
#include <regex>
#include "inja/inja.hpp"

namespace CmpCGListFiles {
    /**
     * ディレクトリから正規表現とマッチするファイル名を返す
     * @param dir ディレクトリ
     * @param reg 正規表現
     * @return マッチしたファイル名の一覧．
     * @retval ==nullopt dirの調査失敗
     * @retval !=nullopt dirの調査成功
     */
    const std::optional<inja::json::array_t> ListFilesInDir(const std::filesystem::path& dir, const std::regex& reg) noexcept;
}
