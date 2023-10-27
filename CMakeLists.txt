cmake_minimum_required(VERSION 3.24)
project(untitled15)

set(CMAKE_CXX_STANDARD 17)

#recommended by aman to match test environment
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

#pull in desired version of catch through cmake automatically, make it available
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # seems to work with CLion - if you run into problems, try an older version of catch2 v3
)
FetchContent_MakeAvailable(Catch2)

include_directories(test-unit)

add_executable(Main
        src/main.cpp src/headergs.h src/maings.cpp)

add_executable(Tests
        test-unit/test.cpp)

# debugging
## Ensure the source files exist in the specified paths
#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
#    add_executable(Main src/main.cpp)
#else()
#    message(WARNING "Cannot find src/main.cpp!")
#endif()
#
#if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/test-unit/test.cpp)
#    add_executable(Tests test-unit/test.cpp)
#    target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
#else()
#    message(WARNING "Cannot find test-unit/test.cpp!")
#endif()

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain) #link catch to test.cpp file
# the name here must match that of your testing executable (the one that has test.cpp)
