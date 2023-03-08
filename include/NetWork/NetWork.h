#ifndef NETWORK
#define NETWORK


#include "AppManage.h"
#include "USock.h"
#include "TSock.h"


#ifdef _WIN32
typedef HANDLE CtrlHandle;
#endif // _WIN32
#ifdef __linux__
typedef int	CtrlHandle;
#endif // __linux__


//windows IOCP 相关结构体定义
#ifdef _WIN32
#define MAX_BUFFER_LEN 4096

enum OPERATION_TYPE {
	READ,
	WRITE
};

typedef struct                                               // 保存与客户端相连套接字
{
	SOCKET m_clientSock;
	SOCKADDR_IN m_clientAddr;
}PER_HANDLE_DATA, * LPPER_HANDLE_DATA;

typedef struct _PER_IO_CONTEXT {
	OVERLAPPED   m_Overlapped;          // 每一个重叠I/O网络操作都要有一个
	SOCKET       m_sockAccept;          // 这个I/O操作所使用的Socket，每个连接的都是一样的
	WSABUF       m_wsaBuf;              // 存储数据的缓冲区，用来给重叠操作传递参数的，关于WSABUF后面还会讲
	char         m_szBuffer[MAX_BUFFER_LEN]; // 对应WSABUF里的缓冲区
	OPERATION_TYPE  m_OpType;               // 标志这个重叠I/O操作是做什么的，例如Accept/Recv等

} PER_IO_CONTEXT, * PPER_IO_CONTEXT;
#endif // _WIN32


class NetWork : public Application
{
public:
	NetWork();
	virtual ~NetWork() override;

	//原型克隆函数
	NetWork* Clone() const override;

public:
	//重写基类纯虚函数
	void Running() override;

	void Stop() override;

	void* RegistWith() override;

private:
	//外部链接处理线程
	void ResponseProcThread();

private:
	bool m_exit;	//是否退出

	CtrlHandle m_AsyncIoHandle;		//异步io模型句柄
};


#endif // !NETWORK
