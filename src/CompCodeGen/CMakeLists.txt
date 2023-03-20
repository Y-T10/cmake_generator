add_library(CmpCG)

# Target sources
target_sources(CmpCG PRIVATE
CmpCGProject.cpp
CmpCGLibrary.cpp
CmpCGUtility.cpp
)

target_include_directories(CmpCG PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(CmpCG PRIVATE
cxxopts::cxxopts
pantor::inja
CmpRender
CmpConf
)