#pragma once

#include <string_view>

namespace CmpConf {
    /**
     * @brief cmake_minimum_requiredに与えるバージョンの既定値
     * @return "<major>.<minor>.<patch>"
     */
    const std::string_view DefaultCMakeVersion() noexcept;
}