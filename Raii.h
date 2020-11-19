// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#pragma once
#include <iostream>
#include "windows.h"

class CCSGuard // TODO что за название, где final, const, noexcept
{
public:
	CCSGuard(LPCRITICAL_SECTION section);  
	~CCSGuard();
	
private:
	CRITICAL_SECTION *m_res_section;
};

class Synchronisation 
{
public:
	Synchronisation();
	~Synchronisation();
	
	operator LPCRITICAL_SECTION();

	
private:
	CRITICAL_SECTION m_section;	
};

/*  “ы в классе хранишь свою обертку над критической секцией - ты это сделал
	“ам, где надо провести синхронную операцию, ты должен вызывать обертку над операци€ми 
	блокировки - котора€ заблокирует, а потом разблокирует секцию

	Resource - это тво€ обертка блокировки.
	*/