project(uniassert)

option(UNIASSERT_TESTS "Build uniassert tests" OFF)

add_library(${PROJECT_NAME} INTERFACE)
add_library(2gis::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_sources(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include/uniassert/uniassert.h
)


if (UNIASSERT_TESTS)
    find_package(GTest REQUIRED)

    enable_testing()

    set(TEST_PROJECT ${PROJECT_NAME}_test)

    add_executable(${TEST_PROJECT}
        test/main.cpp
        test/system_assert_header.h
        test/test_exception.h
        test/undef.h
        test/uni_assert.cpp
        test/uni_check_return.cpp
        test/uni_check_throw.cpp
        test/uni_disable_asserts.cpp
        test/uni_disable_asserts_with_uni_enable_dynamic_assert_handler.cpp
        test/uni_disable_asserts_with_uni_enable_static_assert_handler.cpp
        test/uni_disable_asserts_with_uni_force_asserts.cpp
        test/uni_enable_dynamic_assert_handler.cpp
        test/uni_enable_dynamic_assert_handler_with_uni_enable_static_assert_handler.cpp
        test/uni_enable_dynamic_assert_handler_with_uni_system_assert_header.cpp
        test/uni_enable_static_assert_handler.cpp
        test/uni_ensure_return.cpp
        test/uni_ensure_throw.cpp
        test/uni_force_asserts.cpp
        test/uni_function.cpp
        test/uni_function_redefined.cpp
        test/uni_system_assert.cpp
        test/uni_system_assert_header.cpp
        test/uni_verify_disabled_asserts.cpp
        test/uni_verify_enabled_asserts.cpp
    )

    target_link_libraries(${TEST_PROJECT}
        ${PROJECT_NAME}
        GTest::GTest
    )
    target_include_directories(${TEST_PROJECT}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )
    set_target_properties(${TEST_PROJECT}
        PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED YES
            CXX_EXTENSIONS NO
    )
    add_test(NAME ${PROJECT_NAME} COMMAND ${TEST_PROJECT})
endif (UNIASSERT_TESTS)
