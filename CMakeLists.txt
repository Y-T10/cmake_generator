cmake_minimum_required(VERSION 3.29.6...3.29.6)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(cmake_generator VERSION 0.0.0 LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(library)
add_subdirectory(templates)
