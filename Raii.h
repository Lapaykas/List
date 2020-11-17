#pragma once
#include <iostream>
#include "windows.h"

class Resource // TODO ��� �� ��������, ��� final, const, noexcept
{
public:
	Resource(CRITICAL_SECTION* section)  //TODO � ������ �� ������ ��� ������� ���������� � cpp? ���� ��� �����, ���� ��� ����. 
	{
		m_res_section = *section; //TODO ����� ������. ����� �����������
		lock();		
	}
	~Resource() 
	{
		unlock();
	}
	void lock(); //TODO ���������� �������
	void unlock(); //������ �������
private:
	CRITICAL_SECTION m_res_section;
};

class Raii // TODO ��� �� ��������
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

	//operator LPCRITICAL_SECTION() {}; //TODO ���?

	void lock() //������ ������� � �� ����������. ��� ������ lock ������� � ����� ����������� Resource
	{
		Resource res(&m_section);
	}
private:
	CRITICAL_SECTION m_section;
};

/*  �� � ������ ������� ���� ������� ��� ����������� ������� - �� ��� ������
	���, ��� ���� �������� ���������� ��������, �� ������ �������� ������� ��� ���������� 
	���������� - ������� �����������, � ����� ������������ ������

	Resource - ��� ���� ������� ����������.
	*/