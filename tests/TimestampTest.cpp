#include <cassert>
#include <iostream>

#include "log/Timestamp.hpp"

void test_valid_timestamp()
{
    Timestamp timestamp;

    assert(timestamp.validate_time(
        "[2026-08-31, 11:53:40 UTC]"
    ));
}

void test_invalid_format()
{
    Timestamp timestamp;

    assert(!timestamp.validate_time(
        "2026-08-31, 11:53:40 UTC"
    ));

    assert(!timestamp.validate_time(
        "[2026-08-31 11:53:40 UTC]"
    ));

    assert(!timestamp.validate_time(
        "[2026/08/31, 11:53:40 UTC]"
    ));

    assert(!timestamp.validate_time(
        "[2026-8-31, 11:53:40 UTC]"
    ));
}

void test_invalid_time()
{
    Timestamp timestamp;

    assert(!timestamp.validate_time(
        "[2026-08-31, 25:53:40 UTC]"
    ));

    assert(!timestamp.validate_time(
        "[2026-08-31, 11:60:40 UTC]"
    ));

    assert(!timestamp.validate_time(
        "[2026-08-31, 11:53:60 UTC]"
    ));
}

void test_invalid_date()
{
    Timestamp timestamp;

    assert(!timestamp.validate_time(
        "[2026-13-31, 11:53:40 UTC]"
    ));

    assert(!timestamp.validate_time(
        "[2026-04-31, 11:53:40 UTC]"
    ));

    assert(!timestamp.validate_time(
        "[2026-02-30, 11:53:40 UTC]"
    ));
}

void test_leap_year()
{
    Timestamp timestamp;

    // Valid leap years
    assert(timestamp.validate_time(
        "[2024-02-29, 11:53:40 UTC]"
    ));

    assert(timestamp.validate_time(
        "[2000-02-29, 11:53:40 UTC]"
    ));

    // Invalid leap years
    assert(!timestamp.validate_time(
        "[2023-02-29, 11:53:40 UTC]"
    ));

    assert(!timestamp.validate_time(
        "[1900-02-29, 11:53:40 UTC]"
    ));
}

int main()
{
    test_valid_timestamp();
    test_invalid_format();
    test_invalid_time();
    test_invalid_date();
    test_leap_year();

    std::cout << "All Timestamp tests passed.\n";

    return 0;
}