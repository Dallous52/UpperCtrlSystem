#ifndef MSOCKET
#define MSOCKET

#ifdef _WIN32

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif // _MSC_VER

#include <Winsock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Kernel32.lib")

#endif // _WIN32

#ifdef __linux__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#endif // __linux__

#include <stdint.h>
#include <string>

using std::string;

#ifdef _WIN32
typedef SOCKET SOCK;
#endif // _WIN32

#ifdef __linux__
typedef int SOCK;
#endif // __linux__


enum SubmitType
{
	CONNECT,
	BIND_LISTEN,
	P_TO_P
};


//网络Socket基类
class MSocket
{
public:
	MSocket(SubmitType submit)
	{
		submitType = submit;
		m_port = 0;
	}

	virtual ~MSocket() {}

public:
	//链接到主机
	virtual SOCK ConnectTo() = 0;

	//监听或绑定本机端口
	virtual SOCK BindOrListen() = 0;

public:
	SubmitType submitType;	//申请链接类型

	string host;			//链接主机地址
	uint16_t m_port;		//链接绑定端口
};


#endif // !MSOCKET
