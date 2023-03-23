#pragma once

#include <optional>
#include "cxxopts.hpp"
#include "inja/inja.hpp"
#include <ostream>

namespace CmpCG {
    /// @brief プロジェクト関係のオプションを設定する
    /// @param opt オプションオブジェクト
    void OptionBin(cxxopts::Options& opt) noexcept;

    /// @brief 引数のパース結果からテンプレートのプロパティを生成する
    /// @param result パース結果
    /// @return 生成したプロパティ
    /// @retval ==nullopt プロパティ生成失敗
    /// @retval !=nullopt プロパティ生成成功
    const std::optional<inja::json> ArgParseBin(const cxxopts::ParseResult& result) noexcept;
    
    /// @brief パラメータからテンプレートファイルへのパスを返す
    /// @param result パース結果
    /// @return テンプレートファイルへのパウ
    const std::filesystem::path TplPathBin(const cxxopts::ParseResult& result) noexcept;
};