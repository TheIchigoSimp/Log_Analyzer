#include <cassert>
#include <chrono>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "log/LogAnalyzer.hpp"

int main()
{
    const std::string file_path = "LogAnalyzerTest.log";
    {
        std::ofstream output(file_path);
        output << "[2026-08-31, 11:53:40 UTC] {src/main.cpp:1} INFO Started\n";
        output << "not a structured log\n";
        output << "[2026-08-31, 11:54:10 UTC] {src/main.cpp:2} ERROR Failed\n";
        output << "[2026-08-31, 11:54:00 UTC] {src/main.cpp:3} WARNING Slow\n";
    }

    LogAnalyzer analyzer;
    const auto stats = analyzer.analyze_file(file_path);

    assert(stats.total_lines == 4);
    assert(stats.structured_logs == 3);
    assert(stats.unstructured_logs == 1);
    assert(stats.info_count == 1);
    assert(stats.warning_count == 1);
    assert(stats.error_count == 1);
    assert(stats.debug_count == 0);
    assert(stats.has_time_range);
    assert(stats.start_timestamp == "[2026-08-31, 11:53:40 UTC]");
    assert(stats.end_timestamp == "[2026-08-31, 11:54:10 UTC]");
    assert(std::chrono::duration_cast<std::chrono::seconds>(
        stats.elapsed_time).count() == 30);

    std::remove(file_path.c_str());
    std::cout << "All LogAnalyzer tests passed.\n";
    return 0;
}