add_executable(tcm)

set_target_properties(tcm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Target sources
target_sources(tcm PRIVATE
AppMainMain.cpp
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(tcm PRIVATE
CmpRender
pantor::inja
fmt::fmt
cxxopts::cxxopts
)