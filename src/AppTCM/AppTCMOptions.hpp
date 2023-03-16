#pragma once

#include "cxxopts.hpp"
#include<string>

namespace AppMain {
    /// アプリケーションの引数のパース結果
    using AppOption = cxxopts::ParseResult;

    // アプリケーションの引数をパースした結果を返す
    const AppOption ParseOptions(const std::string& name, const std::string& desc, const int argc, const char* argv[]) noexcept;

    /// アプリケーションの引数を扱うオブジェクトを返す
    const cxxopts::Options CreateAppOptions(const std::string& name, const std::string& desc) noexcept;
}