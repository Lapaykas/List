#pragma once
#include <iostream>
#include "windows.h"

class Resource // TODO что за название, где final, const, noexcept
{
public:
	Resource(CRITICAL_SECTION* section)  //TODO а почему ты только две функции реализовал в cpp? либо все здесь, либо все туда. 
	{
		m_res_section = *section; //TODO херню сделал. Зачем разименовал
		lock();		
	}
	~Resource() 
	{
		unlock();
	}
	void lock(); //TODO Именование функций
	void unlock(); //Лишние функции
private:
	CRITICAL_SECTION m_res_section;
};

class Raii // TODO что за название
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

	//operator LPCRITICAL_SECTION() {}; //TODO где?

	void lock() //Лишняя функция и не правильная. При вызове lock берется и сразу отпускается Resource
	{
		Resource res(&m_section);
	}
private:
	CRITICAL_SECTION m_section;
};

/*  Ты в классе хранишь свою обертку над критической секцией - ты это сделал
	Там, где надо провести синхронную операцию, ты должен вызывать обертку над операциями 
	блокировки - которая заблокирует, а потом разблокирует секцию

	Resource - это твоя обертка блокировки.
	*/