set(INJA_USE_EMBEDDED_JSON ON)
set(INJA_INSTALL OFF)
set(INJA_EXPORT OFF)
set(BUILD_TESTING OFF)
set(INJA_BUILD_TESTS OFF)
set(BUILD_BENCHMARK OFF)
set(COVERALLS OFF)
add_subdirectory(inja)

set(FMT_INSTALL OFF)
add_subdirectory(fmt)

add_subdirectory(cppopts)
