#pragma once
#include <iostream>
#include "windows.h"

class Resource
{
public:
	Resource(CRITICAL_SECTION* section)
	{
		m_res_section = *section;
		lock();		
	}
	~Resource() 
	{
		unlock();
	}
	void lock();
	void unlock();
private:
	CRITICAL_SECTION m_res_section;
};

class Raii
{
public:
	Raii()
	{
		InitializeCriticalSection(&m_section);		
	}
	~Raii()
	{		
		DeleteCriticalSection(&m_section);
	}

	void lock()
	{
		Resource res(&m_section);
	}
private:
	CRITICAL_SECTION m_section;
};