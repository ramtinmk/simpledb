cmake_minimum_required(VERSION 3.16)
project(SimpleDB
    VERSION 0.1.0
    DESCRIPTION "A simple single-node relational DBMS from scratch"
    LANGUAGES CXX
)

# ----------------------------
# Global Settings
# ----------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Output directory organization
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# ----------------------------
# Collect Sources
# ----------------------------
file(GLOB_RECURSE SIMPLEDB_SOURCES
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

# ----------------------------
# Core Library (for reuse / tests / server)
# ----------------------------
add_library(simpledb_core ${SIMPLEDB_SOURCES})

target_include_directories(simpledb_core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Optional: Add warnings
if (MSVC)
    target_compile_options(simpledb_core PRIVATE /W4)
else()
    target_compile_options(simpledb_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ----------------------------
# Executable (the REPL / main entry)
# ----------------------------
add_executable(simpledb
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_link_libraries(simpledb PRIVATE simpledb_core)

# ----------------------------
# Tests (if using CTest)
# ----------------------------
option(SIMPLEDB_BUILD_TESTS "Build unit tests" ON)

if(SIMPLEDB_BUILD_TESTS)
    enable_testing()

    # Example: use Catch2 / GTest if you add them later
    file(GLOB_RECURSE TEST_SOURCES
        ${PROJECT_SOURCE_DIR}/tests/*.cpp
    )

    add_executable(simpledb_tests ${TEST_SOURCES})
    target_link_libraries(simpledb_tests PRIVATE simpledb_core)

    add_test(NAME simpledb_tests COMMAND simpledb_tests)
endif()

# ----------------------------
# Installation Rules
# ----------------------------
install(TARGETS simpledb simpledb_core
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)

message(STATUS "SimpleDB configured successfully!")
