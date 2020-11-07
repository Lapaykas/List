// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ClassList.h"

List::List() : m_size_of_list(0),m_head(nullptr),m_last_element(nullptr)
{	
	
} 

List::~List()
{
	Node* current = this->m_head;
	while (current->m_pNext!=nullptr)
	{
		current = current->m_pNext;
		delete current->m_pPrev;
	}
	delete current;
}

//void List::delete_element(const int index) noexcept
//{
//	Node* temp=find_element(index);
//	temp->m_pNext->m_pPrev = temp->m_pPrev;
//	temp->m_pPrev->m_pNext = temp->m_pNext;
//	delete temp;
//	m_size_of_list--;
//}

void List::push_back(const std::vector<char*>* vector_of_words) noexcept
{
	if (m_head == nullptr)//TODO дублирование кода!
	{
		m_head = new Node(vector_of_words); //TODO - пораждает исключения
		m_last_element = m_head;
	}
	else
	{
		Node* current = this->m_last_element;		
		current->m_pNext = new Node(vector_of_words);	// TODO Это отдельный метод присоединения ноды
		current->m_pNext->m_pPrev = current;			//
		m_last_element = current->m_pNext;
	}
	m_size_of_list++;
}

void List::push_front(const std::vector<char*>* vector_of_words) noexcept
{
	if (m_head == nullptr)
	{
		m_head = new Node(vector_of_words);
		m_last_element = m_head;
	}
	else
	{
		Node* current = this->m_head;
		current->m_pPrev = new Node(vector_of_words);
		current->m_pPrev->m_pNext = current;
		m_head = current->m_pPrev;
	}
	m_size_of_list++;
}

void List::print_list()
{
	Node* current = this->m_head;
	do
	{
		for(int i=0;i<current->m_size_ppWords;i++) //TODO тип i выбран неверно
			std::cout << current->m_ppWords[i] << " ";
 		current = current->m_pNext;
		std::cout << std::endl;
	} while (current != nullptr);
}

//List::Node* List::operator[](const int index)
//{
//	int count;
//	Node* current=nullptr;
//	bool is_head_of_list;
//	if (index <= m_size_of_list / 2)
//	{
//		current = this->m_head;
//		is_head_of_list = true;
//		count = 0;
//	}
//	else
//	{
//		current = this->m_last_element;
//		is_head_of_list = false;
//		count = m_size_of_list-1;
//	}
//	while (current!=nullptr)
//	{
//		if (count == index)
//		{
//			return current;
//		}
//		if (is_head_of_list)
//		{
//			current = current->m_pNext;
//			count++;
//		}
//		else
//		{
//			current = current->m_pPrev;
//			count--;
//		}
//		
//	}
//}





