#include "SysManage.h"

SysManage* SysManage::m_instance = nullptr;


SysManage::SysManage()
{
	m_appManage = AppManage::GetAppManage();
	m_registry = new Registry;
	m_print = mprint::Get();
	m_InteractThread = nullptr;
}


//单线程模式下 Singleton* getInstance() 的实现
SysManage* SysManage::GetSysManange()
{
	if (m_instance == nullptr)
	{
		m_instance = new SysManage;
	}
	return m_instance;
}


bool SysManage::SysInitialize()
{
	m_print->IsSync(false);

	m_registry->RegistryInit();

	m_InteractThread = new thread(&AppManage::AppInteractThread, m_appManage);

	return m_registry->SysAppInit(m_appManage);
}


bool SysManage::AppStart(const string& name)
{
	Application* app = m_registry->GetAppByName(name);

	if (app != nullptr)
	{
		m_appManage->AppStart(name, app);
		return true;
	}

	return false;
}


SysManage::~SysManage()
{
	m_appManage->SystemExit();

	m_appManage->m_exit = true;
	m_InteractThread->join();

	delete m_InteractThread;
	m_InteractThread = nullptr;

	delete m_registry;
	m_registry = nullptr;

	delete m_instance;
	m_instance = nullptr;
}