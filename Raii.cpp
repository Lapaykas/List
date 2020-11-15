#include "Raii.h"

Raii::Raii()
{
	InitializeCriticalSection(&m_section);
	lock();
	std::cout << "Node is attach" << std::endl;
}

Raii::~Raii()
{
	unlock();
	DeleteCriticalSection(&m_section);
	std::cout << "Node is detach" << std::endl;
}

void Raii::lock()
{
	EnterCriticalSection(&m_section);
}

void Raii::unlock()
{
	LeaveCriticalSection(&m_section);
}
