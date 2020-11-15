#pragma once
#include <iostream>
#include "windows.h"

class Raii
{
public:
	Raii();
	~Raii();

	void lock();
	void unlock();
private:
	
	CRITICAL_SECTION m_section;
};
