// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <iostream>
#include "ClassList.h"
#include <sstream>
#include <vector>
#include <process.h>
#include <windows.h>

void stringToList(const std::string& input_string, List* lst)
{
    char* pPos = nullptr; //TODO перенести объявление к использованию
    char* word = nullptr; //TODO объединить инициализацию с объявлением
    std::vector<char*> vector_of_words; //TODO использование локальной переменной
    static const char arrayPunctuationMarks[] = " <>_~`&%@^+=[]{}\\|/!?$;()#*:,.'\"\t\n\r";
    std::vector <char> tmpArrayWords(input_string.size() + 1, '\0');
    memcpy(tmpArrayWords.data(), input_string.c_str(), input_string.size());

    word = strtok_s(tmpArrayWords.data(), arrayPunctuationMarks, &pPos);
    vector_of_words.push_back(word);
    if (word == nullptr)
    {
        return ;
    }    
    while (word != nullptr)
    {
        word = strtok_s(nullptr, arrayPunctuationMarks, &pPos);        
        if (word == nullptr)
        {
            break;
        }        
        vector_of_words.push_back(word);
    }
    lst->push_front(&vector_of_words);
}

void __cdecl AdderThreadProc (void* pArgs)
{
    List* pLst = reinterpret_cast<List*>(pArgs);

    const std::vector<std::string> names_of_military{
     "privet\0", "vojskovaya chast specialnogo naznacheniya gru", "1-ya brigada upravleniya",
     "privet\0", "vojskovaya chast specialnogo naznacheniya gru", "1-ya brigada upravleniya",
     "privet\0", "vojskovaya chast specialnogo naznacheniya gru", "1-ya brigada upravleniya",
     "privet\0", "vojskovaya chast specialnogo naznacheniya gru", "1-ya brigada upravleniya",
     "privet\0", "vojskovaya chast specialnogo naznacheniya gru", "1-ya brigada upravleniya",
     "privet\0", "vojskovaya chast specialnogo naznacheniya gru", "1-ya brigada upravleniya",
     "privet\0", "vojskovaya chast specialnogo naznacheniya gru", "1-ya brigada upravleniya" };

    for (auto it : names_of_military)
    {
        stringToList(it, pLst);
    }
}

int main()
{
    
    List lst;
    std::vector<std::string> names_of_military;  // TODO плохо упаковано, если убрать инициализацию ене работает вовсе
    names_of_military.push_back("privet\0");
    names_of_military.push_back("vojskovaya chast specialnogo naznacheniya gru");
    names_of_military.push_back("1-ya brigada upravleniya");
    names_of_military.push_back("privet\0");
    names_of_military.push_back("vojskovaya chast specialnogo naznacheniya gru");
    names_of_military.push_back("1-ya brigada upravleniya");
    names_of_military.push_back("privet\0");
    names_of_military.push_back("vojskovaya chast specialnogo naznacheniya gru");
    names_of_military.push_back("1-ya brigada upravleniya");
    names_of_military.push_back("privet\0");
    names_of_military.push_back("vojskovaya chast specialnogo naznacheniya gru");
    names_of_military.push_back("1-ya brigada upravleniya");
    names_of_military.push_back("privet\0");
    names_of_military.push_back("vojskovaya chast specialnogo naznacheniya gru");
    names_of_military.push_back("1-ya brigada upravleniya");
    
    for (auto it : names_of_military)
    {
        stringToList(it, &lst);
    } 
    
    //lst.push_back(nullptr); //TODO не работает
    //lst.push_front(nullptr); //TODO не работает

    //List lst2 = lst;  //TODO не работает

    /*HANDLE hTr[5]; //TODO не корректный вывод!
    for (size_t i = 0; i < 5; i++)
    {
        hTr[i] = (HANDLE)_beginthread(AdderThreadProc, 0, &lst);
    }
    WaitForMultipleObjects(5, hTr, TRUE, INFINITE);
    */

    lst.print_list();

    return 0;
}

