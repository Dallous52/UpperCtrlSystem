#include "NetWork.h"
#include "Registry.h"
#include "Log.h"

int isStartup = 0;

NetWork::NetWork() : Application(new mutex, new condition_variable)
{
#ifdef _WIN32
	if (!isStartup)
	{
		WSADATA wsadata;
		int err = WSAStartup(MAKEWORD(2, 2), &wsadata);
		if (err != 0)
		{
			Log::WriteLog(Log::ErrorLog, Log::LOG_FATAL, "WSAStartup  error：%d", WSAGetLastError());

		}
		isStartup = true;
	}
#endif

	m_exit = false;
	m_name = "NetWork";
	isStartup++;
}


NetWork* NetWork::Clone() const
{
	return new NetWork(*this);
}


void* NetWork::RegistWith()
{
	RegistInfo* info = new RegistInfo;

	//应用注册信息填写
	info->app = this;
	info->name = m_name;
	info->openOnce = false;
	info->platform = ALL;

	return info;
}


void NetWork::Running()
{

}


void NetWork::Stop()
{

}


NetWork::~NetWork()
{
#ifdef _WIN32
	if (isStartup == 1)
	{
		int err = WSACleanup();
		if (err != 0)
		{
			Log::WriteLog(Log::ErrorLog, Log::LOG_FATAL, "WSAStartup  error：%d", WSAGetLastError());

		}
	}
#endif // _WIN32

	isStartup--;
}
