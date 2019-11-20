#pragma once

namespace App
{
	namespace Lib
	{
	}
}

class utilityTime
{
public:
	static const uint64_t MILLION;
	static const uint64_t SECOND;
	static const uint64_t MILLISECOND;
	static const uint64_t MICROSECOND;
	static const uint64_t MINUTE;
	static const uint64_t HOUR;
	static const uint64_t DAY;
	static const uint64_t WEEK;

	static const char* DATE_FORMAT;
	static const char* TIME_FORMAT;
	static const char* DATETIME_FORMAT;
	static const char* DATETIME_FORMAT_HOURLY;
	static const char* DATETIME_FORMAT_DAILY;
	static const char* DATETIME_FORMAT_MONTHLY;

	enum class DAY_OF_WEEK
	{
		NONE,
		SUNDAY,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
	};

	utilityTime();
	~utilityTime();

	static void  ToString( std::string& ret, const char* format, uint64_t time );
	static void  ToString( std::string& ret, const char* format, std::tm* time );


};



/* End UtilityDateTime.h */

