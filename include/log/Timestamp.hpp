#include<chrono>
#include<iostream>
#include<sstream>
#include<ctime>
#include<iomanip>

class Timestamp{
	public:
		std::string validate_time(string time);
		std::chrono::time_point parse_time(std::string time);
		std::string format_time(std::std::chrono::time_point time_pt);

	private:
		std::chrono::time_point<std::chrono::system_clock> timestamp;
};
