// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com


#include <iostream>
#include "ClassList.h"
#include <sstream>
#include <vector>


void stringToList(const std::string& input_string, List* lst)
{
    char* pPos = nullptr;
    char* word = nullptr;
    std::vector<char*> vector_of_words;
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


int main()
{
    
    List lst;
    std::vector<std::string> names_of_military; 
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
    
    lst.print_list();


    return 0;
}

