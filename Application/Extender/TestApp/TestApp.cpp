#include "TestApp.h"
#include "Registry.h"

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

TestApp::TestApp() : Application(new mutex, new condition_variable)
{
	m_name = "TestApp";
	m_exit = false;
}


//声明为const成员函数表明该函数无法修改本类的任何成员
TestApp* TestApp::Clone() const
{
	return new TestApp(*this);
}


void* TestApp::RegistWith()
{
	RegistInfo* info = new RegistInfo;

	//应用注册信息填写
	info->app = this;
	info->name = m_name;
	info->openOnce = false;
	info->platform = ALL;

	return info;
}


void TestApp::Running()
{
	while (!m_exit)
	{
		std::cout << "TestApp is running\n";

#ifdef _WIN32
		Sleep(1000);
#endif // _WIN32

#ifdef __linux__
		sleep(1);
#endif // __linux__

	}
}


void TestApp::Stop()
{
	m_exit = true;
}


TestApp::~TestApp()
{}