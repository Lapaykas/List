// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ClassList.h"


List::List() : m_size_of_list(0),m_head(nullptr),m_last_element(nullptr)
{	
	//InitializeCriticalSection(&m_section);
} 

List::~List()
{
	Node* current = this->m_head;
	if (m_head != nullptr)
	{
		while (current->m_pNext != nullptr)
		{
			current = current->m_pNext;
			delete current->m_pPrev;
		}
		delete current;
		//DeleteCriticalSection(&m_section);
	}	
}

List::List(const List& other): m_size_of_list(0)
{		 
	//InitializeCriticalSection(&this->m_section);
	int count = 0;
	Node* current=other.m_head;	
	while (count < other.m_size_of_list)
	{		
		Node* current_copy = new Node(*current);	
		Add_Node(current_copy, false);
		current = current->m_pNext;
		count++;
	}
}

const List& List::operator=(const List& other)
{
	if (&other == this)
		return *this;
	//InitializeCriticalSection(&this->m_section);
	int count = 0;
	Node* current = other.m_head;
	while (count < other.m_size_of_list)
	{
		Node* current_copy = new Node(*current);
		Add_Node(current_copy, false);
		current = current->m_pNext;
		count++;
	}
	return *this;
}


List::Node::Node(const Node& other): m_pNext(nullptr), m_pPrev(nullptr)
{	
	m_word_count = other.m_word_count;     
	this->m_ppWords = new char*[m_word_count];
	for (auto i = 0; i < m_word_count; i++)
	{
		size_t len = (strlen(other.m_ppWords[i]) + 1) * sizeof(char);
		this->m_ppWords[i] = new char[len];
		memcpy(this->m_ppWords[i], other.m_ppWords[i], len);
	}
}

const List::Node& List::Node::operator=(const Node& other)
{
	if (&other == this)
		return *this;
	m_word_count = other.m_word_count;
	this->m_ppWords = new char* [m_word_count];
	for (auto i = 0; i < m_word_count; i++)
	{
		size_t len = (strlen(other.m_ppWords[i]) + 1) * sizeof(char);
		this->m_ppWords[i] = new char[len];
		memcpy(this->m_ppWords[i], other.m_ppWords[i], len);
	}
	return *this;
}



List::List(List&& other) noexcept
{
	//InitializeCriticalSection(&m_section);
	m_size_of_list = other.m_size_of_list;
	m_head = other.m_head;
	m_last_element = other.m_last_element;
	other.m_head = nullptr;	
	other.m_last_element = nullptr;
}

const List& List::operator=(List&& other) noexcept
{
	if (&other == this)
		return *this;
	//InitializeCriticalSection(&m_section);
	m_size_of_list = other.m_size_of_list;
	m_head = other.m_head;
	other.m_head = nullptr;
	m_last_element = other.m_last_element;
	other.m_last_element = nullptr;
	return *this;
}


List::Node::Node(Node&& other) noexcept
{
	m_pNext = other.m_pNext;
	m_pPrev = other.m_pPrev;
	other.m_pNext = nullptr;
	other.m_pPrev = nullptr;
	m_word_count = other.m_word_count;
	m_ppWords = other.m_ppWords;
	other.m_ppWords = nullptr;
}

const List::Node& List::Node::operator=(Node&& other)
{
	if (&other == this)
		return *this;
	m_pNext = other.m_pNext;
	m_pPrev = other.m_pPrev;
	other.m_pNext = nullptr;
	other.m_pPrev = nullptr;
	m_word_count = other.m_word_count;
	m_ppWords = other.m_ppWords;
	other.m_ppWords = nullptr;
	return *this;
}


void List::Push_Back(const std::string& arg_string) noexcept
{			
	Add_Node(arg_string, false);	
}

void List::Push_Front(const std::string& arg_string) noexcept
{		
	Add_Node(arg_string, true);		
}

void List::Add_Node(const std::string& arg_string, bool is_front) noexcept
{	
	try 
	{
		Node* pNew_node = new Node(arg_string);	
		Add_Node(pNew_node, is_front);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void List::Add_Node(Node* pNode, bool is_front) noexcept
{
	CCSGuard lock(SYNC);
	if (m_head == nullptr)
	{
		m_head = m_last_element = pNode;
	}
	else
	{
		if (is_front)
		{
			Node* current = this->m_head;
			current->m_pPrev = pNode;
			current->m_pPrev->m_pNext = current;
			m_head = current->m_pPrev;
		}
		else
		{
			Node* current = this->m_last_element;
			current->m_pNext = pNode;
			current->m_pNext->m_pPrev = current;
			m_last_element = current->m_pNext;
		}
	}
	m_size_of_list++;
	
	//LeaveCriticalSection(&m_section);
}

int List::Get_Size_List() noexcept
{
	return m_size_of_list;
}

void List::print_list()
{
	Node* current = this->m_head;	
	do
	{
		for(auto i=0;i<current->Get_Size_Data();i++)
		{
			std::cout << current->Get_Data()[i] << " ";			
		}
 		current = current->m_pNext;
		std::cout << std::endl;
	} while (current != nullptr);	
}




List::Node::Node(const std::string& arg_string) : m_pPrev(nullptr), m_pNext(nullptr), m_word_count(0), m_ppWords(nullptr)
{
	this->m_ppWords = new char* [Count_Words(arg_string)];	
	
	static const char arrayPunctuationMarks[] = " <>_~`&%@^+=[]{}\\|/!?$;()#*:,.'\"\t\n\r";
	std::vector <char> tmpArrayWords(arg_string.size() + 1, '\0');
	memcpy(tmpArrayWords.data(), arg_string.c_str(), arg_string.size());

	size_t len;
	char* pPos = nullptr; 
	char* word = strtok_s(tmpArrayWords.data(), arrayPunctuationMarks, &pPos); 	
	if (word == nullptr)
	{
		return;
	}
	len = (strlen(word) + 1) * sizeof(char);
	m_ppWords[m_word_count] = new char[len];
	memcpy(m_ppWords[m_word_count], word, len);
	m_word_count++;
	while (word != nullptr)
	{
		word = strtok_s(nullptr, arrayPunctuationMarks, &pPos);
		if (word == nullptr)
		{
			break;
		}
		len = (strlen(word) + 1) * sizeof(char);
		m_ppWords[m_word_count] = new char[len];
		memcpy(m_ppWords[m_word_count], word, len);
		m_word_count++;
	}
}

List::Node::~Node()
{
	for (int i=0; i < m_word_count; i++)
		delete[] this->m_ppWords[i];
	delete[] this->m_ppWords;
}

size_t List::Node::Get_Size_Data() noexcept
{
	return m_word_count;
}

size_t List::Node::Count_Words(const std::string& arg_string)
{
	static const char arrayPunctuationMarks[] = " <>_~`&%@^+=[]{}\\|/!?$;()#*:,.'\"\t\n\r";
	std::vector <char> tmpArrayWords(arg_string.size() + 1, '\0');
	memcpy(tmpArrayWords.data(), arg_string.c_str(), arg_string.size());
	size_t count = 0;
	char* pPos = nullptr;
	char* word = strtok_s(tmpArrayWords.data(), arrayPunctuationMarks, &pPos);

	if (word == nullptr)
	{
		return count;
	}
	count++;
	while (word != nullptr)
	{
		word = strtok_s(nullptr, arrayPunctuationMarks, &pPos);
		if (word == nullptr)
		{
			break;
		}
		count++;
	}
	return count;	
}
 
char const* const* const List::Node::Get_Data()
{	
	return m_ppWords;
}

