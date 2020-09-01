project(uniassert)

if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup()
endif()

option(UNIASSERT_TESTS "Build uniassert tests" OFF)

set(SRC_LIST
    include/uniassert/uniassert.h
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}_IDE OBJECT ${SRC_LIST})
add_library(2gis::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}_IDE PROPERTIES LINKER_LANGUAGE CXX)


option(UNI_ENABLE_DYNAMIC_ASSERT_HANDLER "Enable dynamic assert handler" OFF)

message("UNI_ENABLE_DYNAMIC_ASSERT_HANDLER is ${UNI_ENABLE_DYNAMIC_ASSERT_HANDLER}")
if (UNI_ENABLE_DYNAMIC_ASSERT_HANDLER)
    target_compile_definitions(uniassert
        INTERFACE
            UNI_ENABLE_DYNAMIC_ASSERT_HANDLER
    )
endif(UNI_ENABLE_DYNAMIC_ASSERT_HANDLER)


option(UNI_FORCE_ASSERTS "Enable uniassert force asserts" OFF)

message("UNI_FORCE_ASSERTS is ${UNI_FORCE_ASSERTS}")
if (UNI_FORCE_ASSERTS)
    target_compile_definitions(uniassert
        INTERFACE
            UNI_FORCE_ASSERTS
    )
endif(UNI_FORCE_ASSERTS)


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
    target_compile_features(${TEST_PROJECT}
        PRIVATE
            cxx_std_14)

    add_test(NAME ${PROJECT_NAME} COMMAND ${TEST_PROJECT})
endif (UNIASSERT_TESTS)
