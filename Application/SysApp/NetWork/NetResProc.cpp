#include "NetWork.h"

void NetWork::ResponseProcThread()
{
	Interaction* response;
	MSocket* sock;

	while (!m_exit)
	{
		unique_lock<mutex> reslock(*m_resLock);
		m_resCond->wait(reslock, [this] { return !m_resQueue.empty() || m_exit; });
		if (m_exit) break; // 在等待期间，如果收到退出信号，则退出线程

		response = m_resQueue.front();
		m_resQueue.pop_front();
		reslock.unlock();

		//数据转换为需求数据类型
		sock = static_cast<MSocket*>(response->data);

		switch (sock->submitType)
		{
		case CONNECT:
			sock->ConnectTo();
			break;

		case BIND_LISTEN:
			sock->BindOrListen();
			break;

		case P_TO_P:
			sock->Peer_To_Peer();
			break;

		default:
			break;
		}
	}
}