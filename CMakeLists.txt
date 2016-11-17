cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
cmake_policy(SET CMP0048 NEW)

# cmake submodules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_COURSE_DIR}/cmake")

# version
foreach (level MAJOR MINOR PATCH)
    file(STRINGS include/version.hpp
            _define_${level}
            REGEX "#define PROG_${level}_VERSION")
    string(REGEX MATCH "([0-9]+)" _${level} "${_define_${level}}")
endforeach ()
set(VERSION "${_MAJOR}.${_MINOR}.${_PATCH}")

# project
project(CppPlay VERSION ${VERSION} LANGUAGES CXX)

# options
option(BUILD_TESTS "build tests" ON)

# variables to all sorts of directories
set(${CMAKE_PROJECT_NAME}_ROOT_DIR ${PROJECT_SOURCE_DIR})
set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/third-party)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)

include(ExternalProject)

# compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")

# include
include_directories(${INCLUDE_DIRS})

# for deveopment
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

