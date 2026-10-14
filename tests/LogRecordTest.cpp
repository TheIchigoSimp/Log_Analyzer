#include <cassert>
#include <chrono>
#include <iostream>
#include <string>

#include "log/LogRecord.hpp"

int main()
{
    Timestamp timestamp;
    const std::string timestamp_text = "[2026-08-31, 11:53:40 UTC]";
    timestamp.parse_to_tm(timestamp_text);
    timestamp.parse_to_str(timestamp.get_time_tm());

    SourceLocation source_location;
    source_location.parse_sourceLocation("{src/main.cpp:42}");

    Severity severity;
    severity.parse_to_severity_level("ERROR");

    Message message;
    std::string message_text = "Unable to open configuration file";
    message.set_logMessage(message_text);

    LogRecord record(timestamp, source_location, severity, message);

    assert(record.get_timestamp_tm() == timestamp.get_time_tm());
    assert(record.get_timestamp_str() == timestamp_text);
    assert(record.get_sourcelocation() == std::make_pair(
        std::string("src/main.cpp"), 42U));
    assert(record.get_severity_level() == Severity::Severity_Levels::ERROR);
    assert(record.get_message() == message_text);

    std::cout << "All LogRecord tests passed.\n";
    return 0;
}