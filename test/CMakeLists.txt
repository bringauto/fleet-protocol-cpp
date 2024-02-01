CMAKE_MINIMUM_REQUIRED(VERSION 3.25 FATAL_ERROR)
PROJECT(fleet-protocol C CXX)

SET(CMAKE_CXX_STANDARD 20)

## Add common headers if they were not added yet by parent project
ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/lib/memory_management/)

FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
FILE(GLOB_RECURSE source_test_files "${CMAKE_CURRENT_LIST_DIR}/source/*")
ADD_EXECUTABLE(fleet_protocol_cpp_tests ${source_test_files} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
TARGET_COMPILE_OPTIONS(fleet_protocol_cpp_tests PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
TARGET_LINK_LIBRARIES(fleet_protocol_cpp_tests PUBLIC
                        ${COMMON_HEADERS_TARGET}
                        memory_management
                        ${MODULE_MAINTAINER_TARGET_NAME}
                        external_server
                        ${GTEST_LIBRARIES}
                        -fsanitize=address)
INCLUDE(GoogleTest)
GTEST_DISCOVER_TESTS(fleet_protocol_cpp_tests)