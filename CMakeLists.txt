cmake_minimum_required(VERSION 3.10)
project(MyEncryptProject)

# Set C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories for header files
include_directories(include)

# Add subdirectories for source code and test
add_subdirectory(src)
add_subdirectory(test)

# Find OpenMP package (optional, for compatibility with different compilers)
find_package(OpenMP REQUIRED)

# Add OpenMP flags to the compiler
if(OpenMP_CXX_FOUND)
    # Set CMake policy to allow linking libraries to targets in subdirectories
    cmake_policy(SET CMP0079 NEW)

    # Apply OpenMP flags to the targets
    target_compile_options(MyLibrary PRIVATE ${OpenMP_CXX_FLAGS})
    target_compile_options(MyTestExecutable PRIVATE ${OpenMP_CXX_FLAGS})

    # Link against the OpenMP library
    target_link_libraries(MyLibrary PRIVATE OpenMP::OpenMP_CXX)
    target_link_libraries(MyTestExecutable PRIVATE OpenMP::OpenMP_CXX)
endif()
