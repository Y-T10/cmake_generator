#include "CmpVerVersion.hpp"

#include "fmt/format.h"

using namespace std;
using namespace fmt;

namespace CmpVer {
// バージョンを文字列に変える関数
const string toString(const Version& v) noexcept {
    return format(FMT_STRING("{:d}.{:d}.{:d}"), v.major, v.minor, v.patch);
}
}