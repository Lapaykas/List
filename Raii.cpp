#include "Raii.h"
#include "atlbase.h"




void Resource::lock()
{
	EnterCriticalSection(&m_res_section);
	std::cout << "Node is attach" << std::endl;
}

void Resource::unlock()
{
	LeaveCriticalSection(&m_res_section);
	std::cout << "Node is detach" << std::endl;
}
