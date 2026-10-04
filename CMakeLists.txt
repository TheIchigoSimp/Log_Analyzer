cmake_minimum_required(VERSION 3.20)

project(Log_Analyzer LANGUAGES CXX)

# Create logging library
add_library(logging
    src/log/Timestamp.cpp
    src/log/Severity.cpp
)
target_include_directories(logging
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# C++ 20
target_compile_features(logging PRIVATE cxx_std_20)

add_executable(log_analyzer
    src/main.cpp
)

# Public headers
target_include_directories(log_analyzer
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_compile_features(log_analyzer PRIVATE cxx_std_20)

# Link logging library
target_link_libraries(log_analyzer PRIVATE logging)

# Tests
include(CTest)
enable_testing()

add_executable(sample_test
    tests/sample_test.cpp
)

target_compile_features(sample_test PRIVATE cxx_std_20)
target_link_libraries(sample_test PRIVATE logging)
add_test(
    NAME SampleTest
    COMMAND sample_test
)
set_property(
    TEST SampleTest
    PROPERTY LABELS "unit"
)

add_executable(TimestampTest
    tests/TimestampTest.cpp
)
target_include_directories(TimestampTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(TimestampTest PRIVATE cxx_std_20)
target_link_libraries(TimestampTest PRIVATE logging)
add_test(
    NAME TimestampTest
    COMMAND TimestampTest
)

set_property(
    TEST TimestampTest
    PROPERTY LABELS "unit"
)

add_executable(SeverityTest
    tests/SeverityTest.cpp
)
target_include_directories(SeverityTest
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
target_compile_features(SeverityTest PRIVATE cxx_std_20)
target_link_libraries(SeverityTest PRIVATE logging)
add_test(
    NAME SeverityTest
    COMMAND SeverityTest
)

set_property(
    TEST SeverityTest
    PROPERTY LABELS "unit"
)