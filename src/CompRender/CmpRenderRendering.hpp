#pragma once

#define INJA_NOEXCEPTION
#include "inja/inja.hpp"
#include <filesystem>
#include <string>
#include <ostream>

namespace CompRender {
    /// @brief コードを生成しストリームに書き出す
    /// @param out 出力先
    /// @param tplFilePath テンプレートファイルへのパス
    /// @param props プロパティ
    /// @return out
    std::ostream& RenderText(std::ostream& out, const std::filesystem::path& tplFilePath, const inja::json& props) noexcept;

    /**
     * @brief ファイル名にテンプレートファイルの拡張子を付けたファイル名を返す
     */
    const std::filesystem::path AppendTemplateFileExt(const std::string& filename) noexcept;
};