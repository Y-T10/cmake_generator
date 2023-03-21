#pragma once

#include <string_view>
#include <filesystem>

namespace CmpConf {
    /**
     * @brief プログラムのインストール先の接頭辞
     * @return "path/to/install/prefix"
     */
    const std::string_view InstallPrefix() noexcept;

    /**
     * @brief インストールされたプログラムのデータパスを返す
    */
    const std::filesystem::path InstallDataPath() noexcept;
}