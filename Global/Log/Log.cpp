#include "Log.h"
#include "mprint.h"
#include <fstream>
#include <cstring>

void Log::WriteLog(const char* filename, int errLev, const char* error, ...)
{
	mprint* _print = mprint::Get();
	string err;

	//获取可变参数
	va_list vapa;
	va_start(vapa, error);

	char buf[500];
	vsprintf(buf, error, vapa);

	std::ofstream log(filename, std::ios::out | std::ios::app);

	if (!log.is_open())//日志打开失败处理
	{
		err = "$log file open failed : ";
		err += strerror(errno) + '\n';
		_print->output(err);
		return;
	}

	string currTime = GetTime();

	//错误信息输入日志文件
	if (errLev >= 0 && errLev < ERR_NUM)
	{
		err = '$' + currTime + " [" + ErrorInfo[errLev] + "] " + buf + "\n";

		if (errLev < 4)//判断是否输出与屏幕
		{
			_print->output(err, mprint::RED);
		}

		log << err;
	}

	log.close();
}



string Log::GetTime()
{
	string date;
	time_t times;
	struct tm* timed;
	char ansTime[50];

	time(&times); //获取从1900至今过了多少秒，存入time_t类型的timep
	timed = localtime(&times);//用localtime将秒数转化为struct tm结构体

	sprintf(ansTime, "%d-%02d-%02d %02d:%02d:%02d", 1900 + timed->tm_year, 1 + timed->tm_mon,
		timed->tm_mday, timed->tm_hour, timed->tm_min, timed->tm_sec);

	date = ansTime;

	return date;
}
