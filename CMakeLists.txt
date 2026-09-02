cmake_minimum_required(VERSION 3.20)

project(Log_Analyzer LANGUAGES CXX)

include(CTest)
enable_testing()

add_executable(log_analyzer src/main.cpp)

add_executable(sample_test tests/sample_test.cpp)
add_test(NAME SampleTest COMMAND sample_test)
set_property(TEST SampleTest PROPERTY LABELS "unit")

target_compile_features(log_analyzer PRIVATE cxx_std_20)
