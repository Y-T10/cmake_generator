#pragma once

#define INJA_NOEXCEPTION
#include "inja/inja.hpp"
#include <string>
#include <ostream>

namespace CompRender {
    /// @brief propsを用いて生成したコードをストリームに書き出す
    /// @param out 出力先
    /// @param props プロパティ
    /// @return out
    std::ostream& RenderText(std::ostream& out, const std::string& templateName,  const inja::json& props) noexcept;
};