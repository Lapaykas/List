// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include<iostream>
#include <vector>
class List
{
	class Node;
public:
	List();
	~List();
	int m_size_of_list;
	
	//void delete_element(const int index) noexcept;
	void push_back(const std::vector<char*>* vector_of_words) noexcept;
	void push_front(const std::vector<char*>* vector_of_words) noexcept;
	void print_list();
	//List::Node* operator[](const int index);
		
private:	

	class Node
	{
	public:
		Node* m_pPrev;
		Node* m_pNext;
		char** m_ppWords;	
		int m_size_ppWords;

		Node(const std::vector<char*>* vector_of_words) : m_pPrev(nullptr), m_pNext(nullptr), m_size_ppWords(0), m_ppWords(nullptr)
		{							
			this->m_ppWords=new char* [vector_of_words->size()];
			for (auto it : *vector_of_words)
			{						
				size_t len = (strlen(it) + 1) * sizeof(char);
				m_ppWords[m_size_ppWords] = new char[len];
				memcpy(m_ppWords[m_size_ppWords], it, len);				
				m_size_ppWords++;
			}					
		}
	};	

	Node* m_head;
	Node* m_last_element;
};
