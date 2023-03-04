#pragma once

#include "jinja2cpp/value.h"
#include <filesystem>
#include <ostream>

namespace CompRender {
    /// @brief propsを用いて生成したコードをストリームに書き出す
    /// @param out 出力先
    /// @param props プロパティ
    /// @return out
    std::ostream& RenderText(std::ostream& out, const  std::filesystem::path& path,  const jinja2::ValuesMap& props) noexcept;
};