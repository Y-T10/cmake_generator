# define library
add_library(CmpFile)

# Target sources
target_sources(CmpFile PRIVATE
CmpFileSysPath.cpp
)

# Target include directories
target_include_directories(CmpFile PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}
)