#include "NetWork.h"

void NetWork::ResponseProcThread()
{
	Interaction* response;
	MSocket* msock;
	SOCK tempSock;

	while (!m_exit)
	{
		unique_lock<mutex> reslock(*m_resLock);
		m_resCond->wait(reslock, [this] { return !m_resQueue.empty() || m_exit; });
		if (m_exit) break; // 在等待期间，如果收到退出信号，则退出线程

		response = m_resQueue.front();
		m_resQueue.pop_front();
		reslock.unlock();

		//数据转换为需求数据类型
		msock = static_cast<MSocket*>(response->data);

		switch (msock->submitType)
		{
		case CONNECT:
			tempSock = msock->ConnectTo();
			break;

		case BIND_LISTEN:
			tempSock = msock->BindOrListen();
			break;

		case P_TO_P:
			
			break;

		default:
			break;
		}


	}
}