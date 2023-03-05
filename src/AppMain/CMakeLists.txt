add_library(AppMain)

# Target sources
target_sources(AppMain PRIVATE
AppMainMain.cpp
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(AppMain PRIVATE
CmpRender
)