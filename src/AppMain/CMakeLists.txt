add_executable(AppMain)

set_target_properties(AppMain PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Target sources
target_sources(AppMain PRIVATE
AppMainMain.cpp
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(AppMain PRIVATE
CmpRender
pantor::inja
fmt::fmt
)