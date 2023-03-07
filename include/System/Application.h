#ifndef APPLICATION
#define APPLICATION

#include <string>
#include <list>
#include <mutex>
#include <condition_variable>

using std::mutex;
using std::string;
using std::list;
using std::condition_variable;


struct Interaction
{
	string appName;
	void* data;
};


class Application
{
public:
	Application(mutex* lock, condition_variable* cond) : m_resLock(lock), m_resCond(cond) {}

	//原型模式 用于克隆自身
	virtual Application* Clone() const = 0;

	virtual ~Application() {
		delete m_resLock;
		m_resLock = nullptr;

		delete m_resCond;
		m_resCond = nullptr;
	};

public:

	//向应用注册表中添加应用
	virtual void* RegistWith() = 0;

	//调用以使应用运行
	virtual void Running() = 0;

	//调用使应用停止
	virtual void Stop() = 0;

public:
	string m_name;

	list<Interaction*> m_resQueue;
	mutex* m_resLock;
	condition_variable* m_resCond;	//响应队列环境变量
};


#endif // !APPLICATION


