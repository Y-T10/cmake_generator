#include "CmpRenderRendering.hpp"

#include <iostream>

using namespace std;
using namespace inja;

const json CreateProjectMap() noexcept {
    json paramMap;
    paramMap["cmakeVersionMin"] = 3.20;
    paramMap["name"] = "";
    paramMap["version"] = "0.0.0";
    paramMap["language"] = "CXX";
    paramMap["defBuildType"] = "Release";
    paramMap["policies"] = {};
    paramMap["include"] = {};
    paramMap["package"] = {};
    paramMap["subdirecotrie"] = {};

    json projectMap;
    projectMap.emplace("project", paramMap);
    return projectMap;
};

int main(int argc, char* argv[]) {
    const json sampleTest = CreateProjectMap();
    CompRender::RenderText(std::cout, "template/projects.template", sampleTest);
    return 0;
};