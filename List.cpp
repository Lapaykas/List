// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <iostream>
#include <sstream>
#include <vector>
#include <process.h>
#include <windows.h>

#include "ClassList.h"



void __cdecl AdderThreadProc (void* pArgs)
{
    List* pLst = reinterpret_cast<List*>(pArgs);
	pLst->Push_Back("privet\0");
	pLst->Push_Back("vojskovaya chast specialnogo naznacheniya gru");
	pLst->Push_Back("1-ya brigada upravleniya");
	pLst->Push_Back("357 uchebniy centr vvs");
	pLst->Push_Back("183-yi mezhvidovoy regionalnyi uchebnyi centr");
}

int main()
{           	    
	List lst;
	HANDLE hTr[2]; //TODO не корректный вывод!
	for (size_t i = 0; i < 2; i++)
	{
		hTr[i] = (HANDLE)_beginthread(AdderThreadProc, 0, &lst);
	}
	WaitForMultipleObjects(2, hTr, TRUE, INFINITE);
	
	lst.print_list();
	std::cout << std::endl;
	//List lst_new=lst;
	List lst_new = std::move(lst);
	lst_new.print_list();
    
    

   
	

	//_CrtMemState s1;
	//_CrtMemCheckpoint(&s1);
	//_CrtMemDumpStatistics(&s1);
	//
	//_CrtMemState s2;
	//_CrtMemCheckpoint(&s2);
	//_CrtMemDumpStatistics(&s2);

    return 0;
}

