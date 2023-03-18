#include "CmpCGListFiles.hpp"

using namespace std;
using namespace std::filesystem;
using namespace inja;

namespace CmpCG {
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
}
