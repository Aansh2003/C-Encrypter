# Set up test executable
add_executable(MyTestExecutable test.cpp)

# Link the test executable with the library (MyLibrary)
target_link_libraries(MyTestExecutable PRIVATE MyLibrary)

# Optionally, link with Google Test framework
find_package(GTest REQUIRED)
target_link_libraries(MyTestExecutable PRIVATE GTest::GTest GTest::Main)

# Register the test executable with CTest
include(GoogleTest)
gtest_discover_tests(MyTestExecutable)
