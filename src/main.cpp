#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include <log/LogAnalyzer.hpp>

namespace {
void print_stats(const LogFileStats &stats)
{
    const double elapsed_seconds =
        std::chrono::duration<double>(stats.elapsed_time).count();

    std::cout << "File: " << stats.file_path << '\n'
              << "  Total logs: " << stats.total_lines << '\n'
              << "  Structured logs: " << stats.structured_logs << '\n'
              << "  Unstructured logs: " << stats.unstructured_logs << '\n'
              << "  DEBUG: " << stats.debug_count << '\n'
              << "  INFO: " << stats.info_count << '\n'
              << "  WARNING: " << stats.warning_count << '\n'
              << "  ERROR: " << stats.error_count << '\n'
              << "  UNKNOWN: " << stats.unknown_count << '\n';

    if (stats.has_time_range) {
        std::cout << "  Start: " << stats.start_timestamp << '\n'
                  << "  End: " << stats.end_timestamp << '\n'
                  << std::fixed << std::setprecision(3)
                  << "  Elapsed seconds: " << elapsed_seconds << '\n';
    } else {
        std::cout << "  Time range: unavailable\n";
    }
}
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: log_analyzer <log-file> [log-file ...]\n";
        return 1;
    }

    std::vector<std::string> file_paths(argv + 1, argv + argc);
    LogAnalyzer analyzer;
    try {
        for (const auto &stats : analyzer.analyze_files(file_paths)) {
            print_stats(stats);
        }
    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}