
if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup()
endif()
