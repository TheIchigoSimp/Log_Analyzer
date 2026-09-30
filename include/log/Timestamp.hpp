#include<chrono>
#include<string>

class Timestamp{
	public:
		bool validate_time(std::string time);
		std::chrono::system_clock::time_point parse_to_tm(std::string time);
		std::string parse_to_str(std::chrono::system_clock::time_point time_pt);

	private:
		std::chrono::system_clock::time_point timestamp;
};
