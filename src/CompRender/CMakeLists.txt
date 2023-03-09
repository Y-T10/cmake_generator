add_library(CmpRender)

# Target sources
target_sources(CmpRender PRIVATE
CmpRenderRendering.cpp
)

target_include_directories(CmpRender PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(CmpRender PRIVATE
    pantor::inja
)
