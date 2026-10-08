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

    severity.parse_to_severity_level("DEBUG");
    assert(severity.get_severity() == Severity::Severity_Levels::DEBUG);
    severity.parse_to_severity_level("INFO");
    assert(severity.get_severity() == Severity::Severity_Levels::INFO);
    severity.parse_to_severity_level("WARNING");
    assert(severity.get_severity() == Severity::Severity_Levels::WARNING);
    severity.parse_to_severity_level("ERROR");
    assert(severity.get_severity() == Severity::Severity_Levels::ERROR);
    severity.parse_to_severity_level("UNKNOWN");
    assert(severity.get_severity() == Severity::Severity_Levels::UNKNOWN);
    severity.parse_to_severity_level("WARN");
    assert(severity.get_severity() == Severity::Severity_Levels::UNKNOWN);
}

int main()
{
    test_valid_severities();
    test_invalid_severities();
    test_parse_to_severity_level();

    std::cout << "All Severity tests passed.\n";
    return 0;
}
