#ifndef NETWORK
#define NETWORK

#include "AppManage.h"
#include "USock.h"
#include "TSock.h"

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
	void ResponseProcThread();

private:
	bool m_exit;	//是否退出
};


#endif // !NETWORK
