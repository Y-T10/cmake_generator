add_executable(tcm)

set_target_properties(tcm PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

get_target_property(PROGRAM_NAME tcm NAME)
if(PROGRAM_NAME EQUAL "PROGRAM_NAME-NOTFOUND")
    message(SEND_ERROR "Program name not found!")
endif()
configure_file(AppBuildConf.cpp.in AppBuildConf.cpp @ONLY)

# Target sources
target_sources(tcm PRIVATE
AppTCMMain.cpp
AppBuildConf.cpp
)

target_include_directories(tcm PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)

# Target libraries
# パッケージライブラリなら
target_link_libraries(tcm PRIVATE
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
install(TARGETS tcm DESTINATION ${CMAKE_INSTALL_BINDIR})