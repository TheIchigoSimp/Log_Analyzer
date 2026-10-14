#include <cassert>
#include <iostream>
#include <stdexcept>

#include "log/LogParser.hpp"

void test_parse_record()
{
    LogParser parser;
    auto record = parser.parse_record(
        "[2026-08-31, 11:53:40 UTC] {src/main.cpp:42} ERROR Unable to open file"
    );

    assert(record.get_timestamp_str() == "[2026-08-31, 11:53:40 UTC]");
    assert(record.get_sourcelocation() == std::make_pair(
        std::string("src/main.cpp"), 42U));
    assert(record.get_severity_level() == Severity::Severity_Levels::ERROR);
    assert(record.get_message() == "Unable to open file");
}

void test_reject_invalid_records()
{
    LogParser parser;
    const char *invalid_records[] = {
        "2026-08-31, 11:53:40 UTC {src/main.cpp:42} ERROR message",
        "[2026-08-31, 25:53:40 UTC] {src/main.cpp:42} ERROR message",
        "[2026-08-31, 11:53:40 UTC] src/main.cpp:42 ERROR message",
        "[2026-08-31, 11:53:40 UTC] {src/main.cpp:42} WARN message",
        "[2026-08-31, 11:53:40 UTC] {src/main.cpp:42} ERROR"
    };

    for (const auto *record : invalid_records) {
        bool threw = false;
        try {
            parser.parse_record(record);
        } catch (const std::invalid_argument &) {
            threw = true;
        }
        assert(threw);
    }
}

int main()
{
    test_parse_record();
    test_reject_invalid_records();

    std::cout << "All LogParser tests passed.\n";
    return 0;
}