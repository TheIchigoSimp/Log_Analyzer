#include <chrono>
#include <cstddef>
#include <string>
#include <vector>

struct LogFileStats {
    std::string file_path;
    std::size_t total_lines = 0;
    std::size_t structured_logs = 0;
    std::size_t unstructured_logs = 0;
    std::size_t debug_count = 0;
    std::size_t info_count = 0;
    std::size_t warning_count = 0;
    std::size_t error_count = 0;
    std::size_t unknown_count = 0;
    bool has_time_range = false;
    std::string start_timestamp;
    std::string end_timestamp;
    std::chrono::system_clock::duration elapsed_time{};
};

class LogAnalyzer {
public:
    LogFileStats analyze_file(const std::string &file_path) const;
    std::vector<LogFileStats> analyze_files(
        const std::vector<std::string> &file_paths
    ) const;
};