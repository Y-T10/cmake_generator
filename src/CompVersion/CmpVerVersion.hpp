#pragma once

#include <string>
#include <cstdint>

namespace CmpVer {
/// セマンティックバージョンを表す型
struct Version {
    uint8_t major = 0;
    uint8_t minor = 0;
    uint8_t patch = 0;
};

// バージョンを文字列に変える関数
const std::string toString(const Version& v) noexcept;
}