#pragma once

#define INJA_NOEXCEPTION
#include "inja/inja.hpp"
#include <filesystem>
#include <string>
#include <ostream>
#include <vector>

namespace CompRender {
    /// @brief propsを用いて生成したコードをストリームに書き出す
    /// @param out 出力先
    /// @param props プロパティ
    /// @return out
    std::ostream& RenderText(
    std::ostream& out,
    const std::string& templateName,
    const inja::json& props,
    const std::vector<std::filesystem::path>& additionalSearchDir = {}) noexcept;

    /**
     * @brief ファイル名にテンプレートファイルの拡張子を付けたファイル名を返す
     */
    const std::filesystem::path AppendTemplateFileExt(const std::string& filename) noexcept;
};