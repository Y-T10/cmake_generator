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
    
    const optional<json::array_t>  ListFilesInDir(const path& dir, const regex& reg) noexcept {
        if(!is_directory(dir)){
            return nullopt;
        }

        json::array_t targetFiles = {};
        for (const directory_entry& file : directory_iterator(dir)) {
            if(!file.is_regular_file()){
                continue;
            }
            if(!regex_match(file.path().filename().string(), reg)){
                continue;
            }
            targetFiles.push_back(file.path().filename().string());
        }
        return targetFiles;
    }
};
