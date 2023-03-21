#pragma once

#include <optional>
#include "cxxopts.hpp"
#include "inja/inja.hpp"
#include <ostream>

namespace CmpCG {
    /// @brief プロジェクト関係のオプションを設定する
    /// @param opt オプションオブジェクト
    void OptionProj(cxxopts::Options& opt) noexcept;

    /// @brief 引数のパース結果からテンプレートのプロパティを生成する
    /// @param result パース結果
    /// @return 生成したプロパティ
    /// @retval ==nullopt プロパティ生成失敗
    /// @retval !=nullopt プロパティ生成成功
    const std::optional<inja::json>ArgParseProj(const cxxopts::ParseResult& result) noexcept;
    
    /// @brief プロパティとテンプレートを元にコードを生成する
    /// @param prop 生成に用いるプロパティ
    /// @param out 出力先ストリーム
    void TplPathProj(const inja::json& prop, const cxxopts::ParseResult& result, std::ostream& out) noexcept;
};