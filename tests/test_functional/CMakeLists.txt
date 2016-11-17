add_executable(functional_test
        main.cpp
        )
target_link_libraries(functional_test
        gtest
        )

add_test(functional_test functional_test)