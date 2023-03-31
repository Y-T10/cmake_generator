#include "CmpCGUtility.hpp"

#include <cassert>
#include "CmpFileSysPath.hpp"

using namespace std::filesystem;
using namespace cxxopts;
using namespace inja;
using namespace std;

namespace CmpCGUtil {
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

    const string GetName(const ParseResult& result) noexcept {
        if(result["name"].count()){
            return result["name"].as<string>();
        }

        assert(!!result["output-dir"].count());
        const path outputPath = CmpFile::ResolvePath(result["output-dir"].as<string>());
        assert(exists(outputPath));
        assert(is_directory(outputPath));
        assert(outputPath.has_filename());
        
        return outputPath.filename().string();
    }
};
