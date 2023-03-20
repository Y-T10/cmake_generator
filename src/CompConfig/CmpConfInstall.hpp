#pragma once

#include <string_view>

namespace CmpConf {
    /**
     * @brief プログラムのインストール先の接頭辞
     * @return "path/to/install/prefix"
     */
    const std::string_view InstallPrefix() noexcept;
}