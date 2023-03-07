#ifndef TESTAPP
#define TESTAPP

#include <iostream>
#include "AppManage.h"


class TestApp : public Application
{
public:
	TestApp();
	virtual ~TestApp() override;

	//原型克隆函数
	TestApp* Clone() const override;

public:

	void Running() override;

	void Stop() override;

	void* RegistWith() override;

private:
	bool m_exit;
};

#endif // !TESTAPP
