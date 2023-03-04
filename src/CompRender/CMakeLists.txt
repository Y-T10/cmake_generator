add_library(CmpRender)

# Target sources
target_sources(CmpRender PRIVATE
CmpRenderRendering.cpp
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(CmpRender PRIVATE
jinja2cpp
)