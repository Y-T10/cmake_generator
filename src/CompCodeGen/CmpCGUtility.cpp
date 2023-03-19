#include "CmpCGUtility.hpp"

using namespace std::filesystem;
using namespace inja;
using namespace std;

namespace CmpCGUtil {
    const vector<path> ConvertToPaht(const vector<string>& paths) noexcept {
        vector<path> dst = {};
        transform(paths.begin(), paths.end(), back_inserter(dst), [](const string& str) -> const path{
            if(str.empty()){
                return "";
            }
            if(str.starts_with('/')) {
                return str;
            }
            return current_path() / str;
        });
        return dst;
    };

    const inja::json toJSON(const std::vector<std::string>& strings){
        auto dst = json::array({});
        std::transform(strings.begin(), strings.end(), std::back_inserter(dst), [](const string& str)->const json{
            return json(str);
        });
        return dst;
    }
};
