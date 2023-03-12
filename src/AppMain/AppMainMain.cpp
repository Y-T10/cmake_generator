#include "CmpRenderRendering.hpp"

#include <iostream>

using namespace std;
using namespace inja;

const json CreateProjectMap() noexcept {
    json paramMap;
    paramMap["project"]["cmakeVersionMin"] = "3.20";
    paramMap["project"]["name"] = "";
    paramMap["project"]["version"] = "0.0.0";
    paramMap["project"]["language"] = "CXX";
    paramMap["project"]["defBuildType"] = "Release";
    paramMap["project"]["policies"] = json::array_t{};
    paramMap["project"]["includes"] = json::array_t{};
    paramMap["project"]["packages"] = json::array_t{};
    paramMap["project"]["subdirecotries"] = json::array_t{};
    return paramMap;
};

int main(int argc, char* argv[]) {
    const auto sampleTest = CreateProjectMap();
    CompRender::RenderText(std::cout, "projects.template", sampleTest);
    return 0;
};