# Collect all .cpp source files recursively in the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Add source files to the library
add_library(MyLibrary STATIC ${SOURCES})

# Include directory for library
target_include_directories(MyLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
