#include "Registry.h"


Registry::Registry()
{
	;
}


string Registry::Application_Regist(Application* app, AppType type)
{
	string ret;

	RegistInfo* info = static_cast<RegistInfo*>(app->RegistWith());

	if (info->app == nullptr)
	{
		return "The application point is nullptr.";
	}

	if (IsExist(info->name))
	{
		ret = "App name " + info->name + "is reused.";
		return ret;
	}

	switch (type)
	{
	case SYSTEM_APP:
		m_sysRegistry[info->name] = info;
		break;

	case USER_APP:
		m_appRegistry[info->name] = info;
		break;

	default:
		ret = "No this Type";
		break;
	}


	return ret;
}


bool Registry::SysAppInit(AppManage* appManage)
{
	if (m_sysRegistry.empty())
	{
		return true;
	}

	size_t registSize = m_sysRegistry.size();
	bool success = true;

	for (auto& temp : m_sysRegistry)
	{
		if (!appManage->AppStart(temp.first, temp.second->app))
		{
			std::cout << "System application " << temp.first << " start failed\n";
			success = false;
		}

		if (!(--registSize))	break;

	}

	return success;
}


Registry::~Registry()
{
	for (auto& temp : m_sysRegistry)
	{
		if (temp.second != nullptr)
		{
			if (temp.second->app != nullptr)
			{
				delete temp.second->app;
				temp.second->app = nullptr;
			}

			delete temp.second;
			temp.second = nullptr;
		}
	}

	m_sysRegistry.clear();

	for (auto& temp : m_appRegistry)
	{
		if (temp.second != nullptr)
		{
			if (temp.second->app != nullptr)
			{
				delete temp.second->app;
				temp.second->app = nullptr;
			}

			delete temp.second;
			temp.second = nullptr;
		}
	}

	m_appRegistry.clear();
}