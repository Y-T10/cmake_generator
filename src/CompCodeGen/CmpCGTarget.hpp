#pragma once

#include <optional>
#include "cxxopts.hpp"
#include "inja/inja.hpp"

namespace CmpCGTarget {
    /*
     * @brief ビルドターゲット用のオプションからプロパティを生成する
     * @param result パラメータの結果
     * @return パラメータから生成されたプロパティ
     */
    const inja::json CreateTargetParam(const cxxopts::ParseResult& result) noexcept;
};