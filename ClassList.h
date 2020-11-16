// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#pragma once
#include<iostream>
#include <vector>
#include "windows.h"
#include "Raii.h"

class List
{
	class Node;
public:
	List();
	~List();
	
	List(const List&);
	List(List&&) noexcept;
	const List& operator=(const List&);
	const List& operator=(List&&) noexcept;	
	void Push_Back(const std::string& arg_string) noexcept;
	void Push_Front(const std::string& arg_string) noexcept;
	void Add_Node(const std::string& arg_string, bool is_front) noexcept;
	void Add_Node(Node* pNode,bool is_front) noexcept;
	int Get_Size_List() noexcept;
	void print_list();
		
private:		
	//CRITICAL_SECTION m_section;
	Raii* RAI;
	class Node
	{
	public:		
		Node(const Node&);
		Node(Node&&) noexcept;	
		const Node& operator=(const Node&);
		const Node& operator=(Node&&);
		Node(const std::string& arg_string);	
		~Node();
		size_t Get_Size_Data() noexcept;
		size_t Count_Words(const std::string& arg_string);
		char const* const* const Get_Data();


		Node* m_pPrev;
		Node* m_pNext;
	private:					

		size_t m_word_count;
		char** m_ppWords;
	};	

	Node* m_head;
	Node* m_last_element;	
	int m_size_of_list; 
};



