#include "AppManage.h"
#include "Log.h"


void AppManage::AppInteractThread()
{
	Interaction* request;
	Application* tmpApp;

	while (!m_exit)
	{
		unique_lock<mutex>	reqlock(m_reqLock);
		m_reqCond.wait(reqlock, [this] { return !m_reqQueue.empty() || m_exit; });
		if (m_exit) break; // 在等待期间，如果收到退出信号，则退出线程

		request = m_reqQueue.front();
		m_reqQueue.pop_front();
		reqlock.unlock();

		{
			lock_guard<mutex> appLock(m_appLock);
			if (!m_running.count(request->appName))
			{
				Log::WriteLog(Log::Reminder, Log::LOG_WARN, "Application %s does not exist in the running queue.",
					request->appName.c_str());
				continue;
			}
			tmpApp = m_running[request->appName].app;
		}

		tmpApp->m_resLock->lock();
		tmpApp->m_resQueue.push_back(request);
		tmpApp->m_resLock->unlock();

		tmpApp->m_resCond->notify_one();
	}
}


void AppManage::AppInteractSubmit(Interaction* request)
{
	m_reqLock.lock();
	m_reqQueue.push_back(request);
	m_reqLock.unlock();

	m_reqCond.notify_one();
}