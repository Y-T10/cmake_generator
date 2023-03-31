add_executable(csw)

set_target_properties(csw PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

get_target_property(PROGRAM_NAME csw NAME)
if(PROGRAM_NAME EQUAL "PROGRAM_NAME-NOTFOUND")
    message(SEND_ERROR "Program name not found!")
endif()
configure_file(AppBuildConf.cpp.in AppBuildConf.cpp @ONLY)

# Target sources
target_sources(csw PRIVATE
AppCSWMain.cpp
AppBuildConf.cpp
)

target_include_directories(csw PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_options(csw PRIVATE
    $<${MINGW}:-static -static-libgcc -static-libstdc++>
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(csw PRIVATE
CmpRender
CmpVer
pantor::inja
fmt::fmt
cxxopts::cxxopts
CmpCG
CmpFile
CmpConf
)

# プログラムのインストール設定
install(TARGETS csw DESTINATION ${CMAKE_INSTALL_BINDIR})