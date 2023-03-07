#include "AppManage.h"

AppManage* AppManage::m_instance = nullptr;

AppManage::AppManage()
{
	m_exit = false;
}


AppManage* AppManage::GetAppManage()
{
	if (m_instance == nullptr)
	{
		m_instance = new AppManage;
	}

	return m_instance;
}


bool AppManage::AppStart(string name, Application* app)
{
	if (app == nullptr)
	{
		return false;
	}

	RunInfo runInfo;

	runInfo.app = app;
	runInfo.appThread = new thread(&Application::Running, app);

	m_appLock.lock();
	m_running[name] = runInfo;
	m_appLock.unlock();

	return true;
}


bool AppManage::AppStop(string name)
{
	lock_guard<mutex> stopLock(m_appLock);
	if (!m_running.count(name))
	{
		return false;
	}

	m_running[name].app->Stop();

	m_running[name].appThread->join();

	delete m_running[name].app;
	m_running[name].app = nullptr;

	delete m_running[name].appThread;
	m_running[name].appThread = nullptr;

	m_running.erase(name);

	return true;
}


void AppManage::SystemExit()
{
	if (m_running.empty())
	{
		return;
	}

	size_t runSize = m_running.size();

	for (auto it = m_running.begin(); it != m_running.end(); ++it)
	{
		AppStop(it->first);
	}
}


AppManage::~AppManage()
{
	delete m_instance;
}