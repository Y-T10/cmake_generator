cmake_minimum_required(VERSION 3.20)

project(CMakeTGen VERSION 0.0.0 LANGUAGES CXX)

cmake_policy(SET CMP0076 NEW)
cmake_policy(SET CMP0128 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0128 NEW)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(CMAKE_BUILD_TYPE Release)

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

add_compile_options(-Wall $<$<CONFIG:Debug>:-g3>)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GNUのインストール先ディレクトリを使用
include(GNUInstallDirs)

add_subdirectory(src)
add_subdirectory(library)