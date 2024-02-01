CMAKE_MINIMUM_REQUIRED(VERSION 3.25 FATAL_ERROR)
PROJECT(fleet-protocol C CXX)

SET(CMAKE_CXX_STANDARD 20)

SET(MEMORY_MANAGEMENT_TARGET         memory_management)

## Add common headers if they were not added yet by parent project
IF(NOT TARGET ${COMMON_HEADERS_TARGET})
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/lib/Fleet-Protocol/)
ENDIF ()

IF (NOT TARGET ${MEMORY_MANAGEMENT_TARGET})
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_LIST_DIR}/lib/memory_management/)
ENDIF ()

#ENABLE_TESTING()
FIND_PACKAGE(GTest REQUIRED)
INCLUDE_DIRECTORIES(${GTEST_INCLUDE_DIRS})
FILE(GLOB_RECURSE source_test_files "${CMAKE_CURRENT_LIST_DIR}/source/*")
ADD_EXECUTABLE(fleet_protocol_cpp_tests ${source_test_files} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
TARGET_COMPILE_OPTIONS(fleet_protocol_cpp_tests PRIVATE -Wall -Wextra -Wpedantic -fsanitize=address)
TARGET_LINK_LIBRARIES(fleet_protocol_cpp_tests PUBLIC
                        ${GTEST_LIBRARIES}
                        ${COMMON_HEADERS_TARGET}
                        ${MEMORY_MANAGEMENT_TARGET}
                        external_server
                        ${MODULE_MAINTAINER_TARGET_NAME}
                        -fsanitize=address)
INCLUDE(GoogleTest)
GTEST_DISCOVER_TESTS(fleet_protocol_cpp_tests)