#include "CmpFileSysPath.hpp"

#include <algorithm>

using namespace std;
using namespace std::filesystem;

namespace CmpFile{
    const path HomeDir() noexcept {
        const char* homeDir = getenv("HOME");
        if(homeDir == nullptr){
            return "";
        }
        return path(homeDir);
    }

    const vector<path> ConvertToPaht(const vector<string>& paths) noexcept {
        vector<path> dst = {};
        transform(paths.begin(), paths.end(), back_inserter(dst), [](const string& str) -> const path{
            if(str.empty()){
                return "";
            }
            return ResolvePath(str);
        });
        return dst;
    };

    const path ResolvePath(const path& oldPaht) noexcept {
        std::error_code fsError;
        const auto absPath = canonical(oldPaht, fsError);
        return fsError? "": absPath;
    };
}

