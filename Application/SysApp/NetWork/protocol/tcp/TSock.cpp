#include "TSock.h"

TSock::TSock(SubmitType submit) : MSocket(submit)
{
	m_port = 0;
}


SOCK TSock::ConnectTo()
{
	return 0;
}


SOCK TSock::BindOrListen()
{
	//2 .创建socket(WSASocket与socket的区别)
	SOCK m_sockListen;

#ifdef _WIN32
	m_sockListen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	//3. 设置SO_REUSEADDR
	//端口复用允许在一个应用程序可以把 n 个套接字绑在一个端口上而不出错。
	//设置端口复用函数要在绑定之前调用，而且只要绑定到同一个端口的所有套接字都得设置复用
	int on = 1;
	setsockopt(m_sockListen, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on));

	struct sockaddr_in ServerAddress;
	memset((char*)&ServerAddress, 0, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddress.sin_port = htons(m_port);
	bind(m_sockListen, (struct sockaddr*)&ServerAddress, sizeof(ServerAddress));

	//4. listen  (注意SOMAXCONN)
	listen(m_sockListen, SOMAXCONN);
#endif // _WIN32


	return m_sockListen;
}


TSock::~TSock()
{
	;
}