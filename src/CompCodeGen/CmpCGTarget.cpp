#include "CmpCGTarget.hpp"

#include "CmpCGUtility.hpp"
#include "inja/inja.hpp"
#include "cxxopts.hpp"
#include <optional>
#include <string>
#include <regex>

using namespace cxxopts;
using namespace inja;
using namespace std;

namespace CmpCGTarget {
    const json CreateTargetParam(const ParseResult& result) noexcept {
        const auto sourceFiles = CmpCGUtil::ListFilesInDir(
            result["output-dir"].as<string>(),
            regex(R"(^[\w\-\.]+\.(c\+\+|cxx|cc|cpp)$)")
        );
        if(!sourceFiles.has_value()){
            return {};
        }
    
        return json::object({
            {"name", CmpCGUtil::GetName(result)},
            {"properties", json::array({})},
            {"sources", *sourceFiles},
            {"includeDirs", json::array({"${CMAKE_CURRENT_SOURCE_DIR}"})},
            {"libraries", CmpCGUtil::toJSON(result["lib"].as<std::vector<string>>())}
        });
    };
};