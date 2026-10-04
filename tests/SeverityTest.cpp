#include <cassert>
#include <iostream>

#include "log/Severity.hpp"

void test_valid_severities()
{
    Severity severity;

    assert(severity.validate_severity("DEBUG"));
    assert(severity.validate_severity("INFO"));
    assert(severity.validate_severity("WARNING"));
    assert(severity.validate_severity("ERROR"));
    assert(severity.validate_severity("UNKNOWN"));
}

void test_invalid_severities()
{
    Severity severity;

    assert(!severity.validate_severity("debug"));
    assert(!severity.validate_severity("WARN"));
    assert(!severity.validate_severity(""));
}

void test_parse_to_severity_level()
{
    Severity severity;

    assert(severity.parse_to_severity_level("DEBUG") == Severity::Severity_Levels::DEBUG);
    assert(severity.parse_to_severity_level("INFO") == Severity::Severity_Levels::INFO);
    assert(severity.parse_to_severity_level("WARNING") == Severity::Severity_Levels::WARNING);
    assert(severity.parse_to_severity_level("ERROR") == Severity::Severity_Levels::ERROR);
    assert(severity.parse_to_severity_level("UNKNOWN") == Severity::Severity_Levels::UNKNOWN);
    assert(severity.parse_to_severity_level("WARN") == Severity::Severity_Levels::UNKNOWN);
}

int main()
{
    test_valid_severities();
    test_invalid_severities();
    test_parse_to_severity_level();

    std::cout << "All Severity tests passed.\n";
    return 0;
}