#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <log/LogAnalyzer.hpp>
#include <log/LogParser.hpp>

namespace {
void count_severity(LogFileStats &stats, Severity::Severity_Levels severity)
{
    switch (severity) {
    case Severity::Severity_Levels::DEBUG:
        ++stats.debug_count;
        break;
    case Severity::Severity_Levels::INFO:
        ++stats.info_count;
        break;
    case Severity::Severity_Levels::WARNING:
        ++stats.warning_count;
        break;
    case Severity::Severity_Levels::ERROR:
        ++stats.error_count;
        break;
    case Severity::Severity_Levels::UNKNOWN:
        ++stats.unknown_count;
        break;
    }
}
}

LogFileStats LogAnalyzer::analyze_file(const std::string &file_path) const
{
    std::ifstream input(file_path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open log file: " + file_path);
    }

    LogFileStats stats;
    stats.file_path = file_path;
    LogParser parser;
    std::string line;
    bool has_previous_timestamp = false;
    std::chrono::system_clock::time_point first_timestamp;
    std::chrono::system_clock::time_point last_timestamp;

    while (std::getline(input, line)) {
        ++stats.total_lines;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        try {
            auto record = parser.parse_record(line);
            ++stats.structured_logs;
            count_severity(stats, record.get_severity_level());

            const auto timestamp = record.get_timestamp_tm();
            if (!has_previous_timestamp) {
                first_timestamp = timestamp;
                last_timestamp = timestamp;
                stats.start_timestamp = record.get_timestamp_str();
                stats.end_timestamp = stats.start_timestamp;
                has_previous_timestamp = true;
            } else {
                if (timestamp < first_timestamp) {
                    first_timestamp = timestamp;
                    stats.start_timestamp = record.get_timestamp_str();
                }
                if (timestamp > last_timestamp) {
                    last_timestamp = timestamp;
                    stats.end_timestamp = record.get_timestamp_str();
                }
            }
        } catch (const std::invalid_argument &) {
            ++stats.unstructured_logs;
        }
    }

    stats.has_time_range = has_previous_timestamp;
    if (has_previous_timestamp) {
        stats.elapsed_time = last_timestamp - first_timestamp;
    }
    return stats;
}

std::vector<LogFileStats> LogAnalyzer::analyze_files(
    const std::vector<std::string> &file_paths
) const
{
    std::vector<LogFileStats> results;
    results.reserve(file_paths.size());
    for (const auto &file_path : file_paths) {
        results.push_back(analyze_file(file_path));
    }
    return results;
}