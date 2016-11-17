add_executable(matrix_test
        main.cpp
        )

target_link_libraries(matrix_test
        gtest
        )

add_test(matrix_test matrix_test)