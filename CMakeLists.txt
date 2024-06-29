cmake_minimum_required(VERSION 3.29.6...3.29.6)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)    

project(cmake_generator VERSION 0.0.0 LANGUAGES CXX)

# GNUのインストール先ディレクトリを使用
include(GNUInstallDirs)

# データのインストール先
set(PROJECT_INSTALL_DATA_DIR "${CMAKE_INSTALL_DATAROOTDIR}/${PROJECT_NAME}")

add_subdirectory(src)
add_subdirectory(library)
add_subdirectory(templates)
