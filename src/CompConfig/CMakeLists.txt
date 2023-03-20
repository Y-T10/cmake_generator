# define library
add_library(CmpConf)

configure_file(CmpConfInstall.cpp.in CmpConfInstall.cpp @ONLY)
configure_file(CmpConfCMake.cpp.in CmpConfCMake.cpp @ONLY)

# Target sources
target_sources(CmpConf PRIVATE
CmpConfInstall.cpp
CmpConfCMake.cpp
)

# Target include directories
target_include_directories(CmpConf PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(CmpConf PRIVATE

)