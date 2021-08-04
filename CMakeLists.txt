cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-D_GLIBCXX_USE_CXX14_ABI=0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_COVERAGE "Build coverage" OFF)

project(uctp_genetic_algorithm VERSION 1.2.0)

string(APPEND CMAKE_CXX_FLAGS " -pedantic -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

add_subdirectory(tools/googletest)

if (BUILD_COVERAGE)
    string(APPEND CMAKE_CXX_FLAGS " -lgcov --coverage")
endif ()

add_subdirectory(lib)
add_subdirectory(prog)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

#[[install(TARGETS GeneticAlgorithm
        EXPORT "${PROJECT_NAME}-targets"
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
        )]]

