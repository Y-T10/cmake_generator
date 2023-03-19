#pragma once

#include "inja/inja.hpp"
#include <filesystem>
#include <string>
#include <vector>

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
};
