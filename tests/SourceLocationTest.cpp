#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

#include "log/SourceLocation.hpp"

void test_valid_source_locations()
{
    SourceLocation source_location;

    source_location.parse_sourceLocation("{src/main.cpp:42}");
    const auto location = source_location.get_sourceLoc();
    assert(location.first == "src/main.cpp");
    assert(location.second == 42);

    source_location.parse_sourceLocation("{app.log:1}");
    const auto first_line = source_location.get_sourceLoc();
    assert(first_line.first == "app.log");
    assert(first_line.second == 1);
}

void test_invalid_source_locations()
{
    SourceLocation source_location;

    const std::string invalid_locations[] = {
        "src/main.cpp:42",
        "{src/main.cpp}",
        "{:42}",
        "{src/main.cpp:0}",
        "{src:line}",
        "{src/main.cpp:4294967296}",
        "{src:1:2}"
    };

    for (const auto &location : invalid_locations) {
        bool threw = false;
        try {
            source_location.parse_sourceLocation(location);
        } catch (const std::invalid_argument &) {
            threw = true;
        }
        assert(threw);
    }
}

int main()
{
    test_valid_source_locations();
    test_invalid_source_locations();

    std::cout << "All SourceLocation tests passed.\n";
    return 0;
}
