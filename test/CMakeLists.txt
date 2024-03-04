CMAKE_MINIMUM_REQUIRED(VERSION 3.25 FATAL_ERROR)
PROJECT(fleet-protocol C CXX)

SET(CMAKE_CXX_STANDARD 20)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/lib/memory_management/)

FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
FILE(GLOB_RECURSE source_test_files "${CMAKE_CURRENT_LIST_DIR}/source/*")
ADD_EXECUTABLE(fleet-protocol-cpp-tests ${source_test_files} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
TARGET_COMPILE_OPTIONS(fleet-protocol-cpp-tests PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
TARGET_LINK_LIBRARIES(fleet-protocol-cpp-tests PUBLIC
                        ${COMMON_HEADERS_TARGET}
                        memory_management
                        ${MODULE_MAINTAINER_TARGET_NAME}-static
                        fleet-protocol-interface::module-maintainer-external-server-interface
                        ${GTEST_LIBRARIES}
                        -fsanitize=address)
INCLUDE(GoogleTest)
GTEST_DISCOVER_TESTS(fleet-protocol-cpp-tests)