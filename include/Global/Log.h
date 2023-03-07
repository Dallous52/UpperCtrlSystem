#ifndef _LOG
#define _LOG

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif // _MSC_VER

#include <string>
using std::string;

namespace Log
{
	constexpr auto ErrorLog = "ErrorLog.txt";		//错误日志文件
	constexpr auto Reminder = "Reminder.txt";		//警示日志文件
	constexpr auto PromptInfo = "PromptInfo.txt";	//提示信息文件

	constexpr auto LOG_FATAL = 0;	//致命
	constexpr auto LOG_URGENT = 1;	//紧急
	constexpr auto LOG_SERIOUS = 2;	//严重
	constexpr auto LOG_CRIT = 3;	//批评
	constexpr auto LOG_ERR = 4;		//错误
	constexpr auto LOG_WARN = 5;	//警告 
	constexpr auto LOG_NOTICE = 6;	//注意
	constexpr auto LOG_INFO = 7;	//信息
	constexpr auto LOG_DEBUG = 8;   //调试

	constexpr auto ERR_NUM = 9;		//错误信息数

	//错误号相关名称
	const string ErrorInfo[ERR_NUM] = {
		"fatal",
		"urgent",
		"serious",
		"critical",
		"error",
		"warn",
		"notice",
		"infomation",
		"debuge"
	};

	void WriteLog(const char* filename, int errLev, const char* error, ...);

	string GetTime();
};

#endif // !_LOG
