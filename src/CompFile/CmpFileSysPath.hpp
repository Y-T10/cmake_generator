#pragma once

#include <filesystem>
#include <vector>
#include <string>

namespace CmpFile{
    /**
     * @brief ホームディレクトリへのパスを取得して返す
     * @retval =="" パスの取得に失敗
     * @retval !="" パスの取得に成功
     */
    const std::filesystem::path HomeDir() noexcept;

    /**
     * @brief 文字列のパスを絶対パスに変換する
     * @details 相対パスはカレントディレクトリからの絶対パスに変換される
     * @param srcPaths 文字列のパスのリスト
     * @return 変換されたパスのリスト
     */
    const std::vector<std::filesystem::path> ConvertToPaht(const std::vector<std::string>& srcPaths) noexcept;
}