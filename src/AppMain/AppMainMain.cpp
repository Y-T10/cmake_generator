#include "CmpRenderRendering.hpp"

#include <iostream>

using namespace std;
using namespace jinja2;

const ValuesMap CreateProjectMap() noexcept {
    ValuesMap paramMap;
    paramMap.emplace("cmakeVersionMin", 3.20);
    paramMap.emplace("names", "");
    paramMap.emplace("version", "0.0.0");
    paramMap.emplace("language", "CXX");
    paramMap.emplace("defBuildType", "Release");
    paramMap.emplace("policies", ValuesList{});
    paramMap.emplace("include", ValuesList{});
    paramMap.emplace("package", ValuesList{});
    paramMap.emplace("subdirecotrie", ValuesList{});

    ValuesMap projectMap;
    projectMap.emplace("project", paramMap);
    return projectMap;
};

int main(int argc, char* argv[]) {
    const ValuesMap sampleTest = CreateProjectMap();
    CompRender::RenderText(std::cout, "template/projects.template", sampleTest);
    return 0;
};