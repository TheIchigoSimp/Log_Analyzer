#include<regex>
#include<stdexcept>
#include<chrono>
#include<ctime>
#include<sstream>
#include<iostream>
#include<iomanip>

#include<log/Timestamp.hpp>

static bool is_leap_year(int year){
    if(year%400 == 0)
        return true;
    else if(year%100 == 0)
        return false;
    else if(year%4 == 0)
        return true;

    return false;
}

static int get_dates_in_month(int year, int month){
    if (month == 2){
        if(is_leap_year(year)){
            return 29;
        }
        else
            return 28;
    }

    if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    return 31;
}

bool Timestamp::validate_time(std::string time){
    if(time.size() != 26)
        return false;

    const std::regex pattern(R"(\[([0-9]{4})-([0-9]{2})-([0-9]{2}), ([0-9]{2}):([0-9]{2}):([0-9]{2}) UTC\])");
    std::smatch match;

    if(!std::regex_match(time, match, pattern))
        return false;

    const int year = std::stoi(match[1].str());
    const int month = std::stoi(match[2].str());
    const int date = std::stoi(match[3].str());
    const int hour = std::stoi(match[4].str());
    const int minutes = std::stoi(match[5].str());
    const int seconds = std::stoi(match[6].str());

    return month >= 1 && month <= 12 &&
           date >= 1 && date <= get_dates_in_month(year, month) &&
           hour >= 0 && hour <= 23 &&
           minutes >= 0 && minutes <= 59 &&
           seconds >= 0 && seconds <= 59;
}



std::chrono::system_clock::time_point Timestamp::parse_to_tm(std::string time){
    if (!validate_time(time))
        throw std::invalid_argument("Invalid timestamp: " + time);

    std::tm tm = {};
    std::istringstream ss(time);

    // Parse string into tm
    ss >> std::get_time(&tm, "[%Y-%m-%d, %H:%M:%S UTC]");

    if (ss.fail())
        throw std::invalid_argument("Unable to parse timestamp: " + time);

    //Convert to time_point
    std::time_t tt = ::timegm(&tm);
    timestamp = std::chrono::system_clock::from_time_t(tt);

    return timestamp;
}

std::string Timestamp::parse_to_str(std::chrono::system_clock::time_point time_pt){
    const std::time_t tt = std::chrono::system_clock::to_time_t(time_pt);
    std::tm tm = {};
    gmtime_r(&tt, &tm);

    std::ostringstream output;
    output << std::put_time(&tm, "[%Y-%m-%d, %H:%M:%S UTC]");
    return output.str();
}

