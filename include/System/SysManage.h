#ifndef SYSMANAGE
#define SYSMANAGE

#include "AppManage.h"
#include "Registry.h"
#include "mprint.h"

//单例模式
class SysManage
{
private:
	SysManage();  // 私有构造函数，禁止外部创建对象
	~SysManage(); //确保外部无法直接销毁单例对象
	SysManage(const SysManage&) = delete;  // 禁止拷贝构造函数
	SysManage& operator=(const SysManage&) = delete;  // 禁止赋值运算符

	//单线程时成员
	static SysManage* m_instance;

public:
	//声明静态成员函数，提供外接获取m_instance实例对象;
	static SysManage* GetSysManange();

	//系统初始化
	bool SysInitialize();

	//打开app
	bool AppStart(const string& name);

	//关闭app
	inline bool AppClose(const string& name) {
		return	m_appManage->AppStop(name);
	}


private:
	AppManage* m_appManage;		//应用管理成员
	Registry* m_registry;		//注册表成员
	mprint* m_print;			//信息打印成员

	thread* m_InteractThread;		//应用交互线程
};

#endif // !SYSMANAGE
