CMAKE_MINIMUM_REQUIRED(VERSION 3.25 FATAL_ERROR)
PROJECT(fleet-protocol C CXX)

SET(CMAKE_CXX_STANDARD 20)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/lib/Fleet-Protocol/)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/lib/memory_management/)
INCLUDE(${CMAKE_CURRENT_LIST_DIR}/../CMakeLists.txt)
ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
FILE(GLOB_RECURSE source_test_files "${CMAKE_CURRENT_LIST_DIR}/src/*")
ADD_EXECUTABLE(fleet_protocol_tests ${source_test_files} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
TARGET_COMPILE_OPTIONS(fleet_protocol_tests PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
TARGET_LINK_LIBRARIES(fleet_protocol_tests PUBLIC
                        ${GTEST_LIBRARIES}
                        ${COMMON_HEADERS_TARGET}
                        memory_management
                        external_server
                        ${MODULE_MAINTAINER_TARGET_NAME}
                        -fsanitize=address)
INCLUDE(GoogleTest)
GTEST_DISCOVER_TESTS(fleet_protocol_tests)