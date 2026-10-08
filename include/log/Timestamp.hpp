#include<chrono>
#include<string>

class Timestamp{
	public:
		bool validate_time(std::string time);
		void parse_to_tm(std::string time);
		void parse_to_str(std::chrono::system_clock::time_point time_pt);
		std::chrono::system_clock::time_point get_time_tm(void);
		std::string get_time_str(void);

	private:
		std::chrono::system_clock::time_point timestamp_tm;
		std::string timestamp_str;
};
