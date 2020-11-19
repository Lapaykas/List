// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include "Raii.h"
#include "atlbase.h"

Synchronisation::Synchronisation()
{
	InitializeCriticalSection(&m_section);
}

Synchronisation::~Synchronisation()
{
	DeleteCriticalSection(&m_section);
}

Synchronisation::operator LPCRITICAL_SECTION()
{
	return &m_section;
}

CCSGuard::CCSGuard(LPCRITICAL_SECTION section): m_res_section(section)
{
	EnterCriticalSection(m_res_section);
	std::cout << "Node is attach\n";
}

CCSGuard::~CCSGuard()
{
	LeaveCriticalSection(m_res_section);
	m_res_section = nullptr;
	std::cout << "Node is detach\n";
}
