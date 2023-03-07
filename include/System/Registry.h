#ifndef REGISTRY
#define	REGISTRY

#include <unordered_map>
#include <string>
#include <iostream>

#include "Application.h"
#include "AppManage.h"

using std::unordered_map;
using std::string;

enum AppPlatform
{
	WINDOWS,
	LINUX,
	MAC,
	ALL
};

enum AppType
{
	SYSTEM_APP,
	USER_APP,
};

struct RegistInfo
{
	bool openOnce = false;			//是否只能打开一次
	AppPlatform platform = ALL;		//可运行环境
	Application* app = nullptr;		//应用指针
	string name;					//应用名
};


class Registry
{
public:
	Registry();
	~Registry();

	//初始化注册表
	void RegistryInit();

	//启动系统应用
	bool SysAppInit(AppManage* appManage);

	inline Application* GetAppByName(const string& name) {
		if (!m_appRegistry.count(name))	return nullptr;

		return m_appRegistry[name]->app;
	}


private:
	//系统应用注册
	string Application_Regist(Application* info, AppType type);

	//判断应用名称是否复用
	inline bool IsExist(string appName) {
		if (m_sysRegistry.count(appName) || m_appRegistry.count(appName))	return true;

		return false;
	}


private:
	unordered_map<string, RegistInfo*>	m_sysRegistry;	//系统应用表

	unordered_map<string, RegistInfo*>	m_appRegistry;	//应用表
};

#endif // !REGISTRY
