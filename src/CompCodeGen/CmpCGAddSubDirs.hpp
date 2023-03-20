#pragma once

#include <optional>
#include "cxxopts.hpp"
#include <ostream>
#include <filesystem>

namespace CmpCG {
    /**
     * @brief オブションよりサブディレクトリ追加コードを生成する
     * @param dir 基底ディレクトリ
     * @param resutl オプション
     * @param out 出力先ストリーム
     */
    void GenerateAddSubdir(const std::filesystem::path& dir, const cxxopts::ParseResult& result,  std::ostream& out) noexcept;
}