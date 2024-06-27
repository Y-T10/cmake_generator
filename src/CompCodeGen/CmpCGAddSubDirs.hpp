#pragma once

#include "inja/inja.hpp"
#include "cxxopts.hpp"
#include <filesystem>
#include <optional>

namespace CmpCG {
    /// @brief 引数のパース結果からテンプレートのプロパティを生成する
    /// @param result パース結果
    /// @return 生成したプロパティ
    /// @retval ==nullopt プロパティ生成失敗
    /// @retval !=nullopt プロパティ生成成功
    const std::optional<inja::json> ArgParseAddSubdir(const cxxopts::ParseResult& result) noexcept;
    
    /// @brief パラメータからテンプレートファイルへのパスを返す
    /// @param result パース結果
    /// @return テンプレートファイルへのパウ
    const std::filesystem::path TplPathAddSubdir(const cxxopts::ParseResult& result) noexcept;
}