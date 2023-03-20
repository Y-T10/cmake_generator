#pragma once

#include "inja/inja.hpp"
#include "cxxopts.hpp"
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
#include <regex>

namespace CmpCGUtil {
    /**
     * @brief 文字列パスの配列をpathの配列に変換する
     * @param paths 文字列パスの配列
     * @return 変換されたpathの配列
     */
    const std::vector<std::filesystem::path> ConvertToPaht(const std::vector<std::string>& paths) noexcept;
    
    /**
     * @brief 文字列配列をjsonの配列オブジェクトに変換する
     */
    const inja::json toJSON(const std::vector<std::string>& strings);

    /**
     * ディレクトリから正規表現とマッチするファイル名を返す
     * @param dir ディレクトリ
     * @param reg 正規表現
     * @return マッチしたファイル名の一覧．
     * @retval ==nullopt dirの調査失敗
     * @retval !=nullopt dirの調査成功
     */
    const std::optional<inja::json::array_t> ListFilesInDir(const std::filesystem::path& dir, const std::regex& reg) noexcept;

    /**
     * @brief プログラムの引数から名前を得る．
     * @param result プログラムの引数
     * @return 名前の文字列
    */
    const std::string GetName(const cxxopts::ParseResult& result) noexcept;
};
