#include<chrono>
#include<string>

#include<log/Timestamp.hpp>
#include<log/SourceLocation.hpp>
#include<log/Severity.hpp>
#include<log/Message.hpp>

class LogRecord{
	public:
		LogRecord(Timestamp timestamp, SourceLocation sourcelocation, Severity severity, Message message){
			this->timestamp = timestamp;
			this->sourcelocation = sourcelocation;
			this->severity = severity;
			this->message = message;
		}

		std::chrono::system_clock::time_point get_timestamp_tm(void);
		std::string get_timestamp_str(void);
		
		std::pair<std::string, unsigned int> get_sourcelocation(void);

		Severity::Severity_Levels get_severity_level(void);

		std::string get_message(void);

	private:
		Timestamp timestamp;
		SourceLocation sourcelocation;
		Severity severity;
		Message message;
};
