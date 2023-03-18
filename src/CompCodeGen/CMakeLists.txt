add_library(AppCodeGen)

# Target sources
target_sources(AppCodeGen PRIVATE
AppCGenProject.cpp
AppCGenLibrary.cpp
AppCGListFiles.cpp
)

target_include_directories(AppCodeGen PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(AppCodeGen PRIVATE
cxxopts::cxxopts
pantor::inja
CmpRender
)