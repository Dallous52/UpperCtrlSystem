#include "Registry.h"
#include "TestApp.h"
#include "NetWork.h"

void Registry::RegistryInit()
{
	Application_Regist(new TestApp, USER_APP);

	Application_Regist(new NetWork, SYSTEM_APP);

	//.....
}

