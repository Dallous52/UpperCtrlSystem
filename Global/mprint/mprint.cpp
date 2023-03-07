#include "mprint.h"

mprint* mprint::m_instance = nullptr;

mprint* mprint::Get()
{
	if (m_instance == nullptr)
	{
		m_instance = new mprint;
	}
	return m_instance;
}
