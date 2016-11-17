# data
configure_file(
        ${TESTS_DIR}/include/data.hpp.in
        ${TESTS_DIR}/include/data.hpp
)
include_directories(include)

# gtest
add_subdirectory(googletest EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# add individual tests
add_subdirectory(test_matrix)
add_subdirectory(test_functional)