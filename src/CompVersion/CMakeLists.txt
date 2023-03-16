add_library(CmpVer)

# Target sources
target_sources(CmpVer PRIVATE
CmpVerVersion.cpp
)

target_include_directories(CmpVer PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(CmpVer PRIVATE
fmt::fmt
)
