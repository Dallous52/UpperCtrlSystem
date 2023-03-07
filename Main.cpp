#include "SysManage.h"

int main()
{
	//获取并初始化单例成员
	SysManage* manage = SysManage::GetSysManange();

	manage->SysInitialize();

	string appName;
	while (true)
	{
		std::cin >> appName;
		manage->AppStart(appName);
	}

	return 0;
}