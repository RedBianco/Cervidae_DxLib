
#include "../../appCommonParam.h"
#include "../../appErrorCode.h"
#include "UtilityDateTime.h"

const uint64_t utilityTime::MILLION = 1000000;
const uint64_t utilityTime::SECOND = utilityTime::MILLION;
const uint64_t utilityTime::MILLISECOND = static_cast<uint64_t>(utilityTime::SECOND * 0.001);
const uint64_t utilityTime::MICROSECOND = static_cast<uint64_t>(utilityTime::MILLISECOND * 0.001);
const uint64_t utilityTime::MINUTE = utilityTime::SECOND * 60;
const uint64_t utilityTime::HOUR = utilityTime::MINUTE * 60;
const uint64_t utilityTime::DAY = utilityTime::HOUR * 24;
const uint64_t utilityTime::WEEK = utilityTime::DAY * 7;
const char* utilityTime::DATE_FORMAT = "%Y-%m-%d";
const char* utilityTime::TIME_FORMAT = "%H:%M:%S";
const char* utilityTime::DATETIME_FORMAT = "%Y-%m-%d %H:%M:%S";
const char* utilityTime::DATETIME_FORMAT_HOURLY = "%Y-%m-%d %H:00:00";
const char* utilityTime::DATETIME_FORMAT_DAILY = "%Y-%m-%d 00:00:00";
const char* utilityTime::DATETIME_FORMAT_MONTHLY = "%Y-%m-01 00:00:00";


utilityTime::utilityTime()
{
}
utilityTime::~utilityTime()
{
}

void utilityTime::ToString( std::string& ret, const char* format, uint64_t time )
{
	// NOTE:localtime_r��C����̋K�i��POSIX�Œ�`���ꂽ�֐��ł͂Ȃ��̂ŁA�����������݂���
	auto t = ( time_t )( time / utilityTime::MILLION );
	struct tm jikan;

	errno_t error;
	// NOTE:�������ɂ�localtime_s�Ŏ擾�����l�����Ă������߂�
	//      tm�\���̂̕ϐ��̃A�h���X(localtime�ƈႢ�Atm�\���̂ւ̃|�C���^�łȂ����Ƃɒ���)�ł���A
	//      �������ɂ�localtime�̎��Ɠ����悤��time_t�^�̕ϐ�(time�֐��Ŏ擾��������������Ă������)
	error = localtime_s( &jikan, &t );
	ToString( ret, format, &jikan);
}
void utilityTime::ToString( std::string& ret, const char* format, std::tm* time )
{
	char buffer[ 64 ];
	strftime( buffer, sizeof( buffer ), format, time );
	ret = buffer;
}





















