#include "CStudyList.h"
#include <iostream>

static std::shared_ptr <IStudyStl>  g_pStudyListInstance = nullptr;
static std::once_flag               g_StudyListSingletonFlag;

CStudyList::CStudyList()
{

}

CStudyList::~CStudyList()
{

}

std::shared_ptr<IStudyStl>CStudyList::GetInstance()
{
	std::call_once(g_StudyListSingletonFlag, [&] {
		g_pStudyListInstance = std::shared_ptr<IStudyStl>(new CStudyList());
		});
	return  g_pStudyListInstance;
}

void CStudyList::AddElement()
{
	std::cout << "<--------CStudyList::AddElement-------->" << std::endl;

	if (m_iListTest.size()>10)
	{
		std::cout << " iCount of AddElement is morn than 10!" << std::endl;
		m_iListTest.clear();
		return;
	}
	for (int i = 0; i != 10; i++)
	{
		m_iListTest.push_back(i);
		std::cout << "the value of list  is :" << i<< std::endl;
	}

}

void CStudyList::DeleteAllElement()
{
	std::cout << "<--------CStudyList::DeleteAllElement-------->" << std::endl;
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_iListTest.clear();
}

void CStudyList::PrintAllElement()
{
	std::cout << "<--------CStudyList::PrintAllElemt-------->" << std::endl;
	std::lock_guard<std::mutex> lock(m_Mutex);
	for (auto it = m_iListTest.begin(); it != m_iListTest.end(); ++it)
	{
		std::cout << "the list result is: " << (*it)  << std::endl;
	}

}

