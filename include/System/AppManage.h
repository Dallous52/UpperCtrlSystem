#ifndef APPMANAGE
#define APPMANAGE

#include <unordered_map>
#include <thread>

#include <condition_variable>
#include "Application.h"

using std::unordered_map;
using std::thread;

using std::condition_variable;
using std::unique_lock;
using std::lock_guard;

struct RunInfo
{
	Application* app;
	thread* appThread;
};

//单例模式
class AppManage
{
private:
	AppManage();  // 私有构造函数，禁止外部创建对象
	~AppManage(); //确保外部无法直接销毁单例对象
	AppManage(const AppManage&) = delete;  // 禁止拷贝构造函数
	AppManage& operator=(const AppManage&) = delete;  // 禁止赋值运算符

	//单线程时成员
	static AppManage* m_instance;

public:
	//声明静态成员函数，提供外接获取m_instance实例对象;
	static AppManage* GetAppManage();

	//启动某个应用
	bool AppStart(string name, Application* app);

	//应用间交互请求处理
	void AppInteractThread();

	//提交交互信息
	void AppInteractSubmit(Interaction* request);

	//停止某个应用
	bool AppStop(string name);

	//系统退出，停止所有应用
	void SystemExit();

public:
	bool m_exit;	//是否退出

private:
	unordered_map<string, RunInfo> m_running;	//启动应用管理
	mutex m_appLock;							//应用表互斥锁

	list<Interaction*> m_reqQueue;				//请求队列
	condition_variable	m_reqCond;				//请求队列环境变量
	mutex	m_reqLock;							//请求队列互斥量
};

#endif // !APPMANAGE
