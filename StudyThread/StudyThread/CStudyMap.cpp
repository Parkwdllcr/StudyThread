#include "CStudyMap.h"
#include <iostream>

static std::shared_ptr <IStudyStl>  g_pStudyMapInstance = nullptr;
static std::once_flag               g_StudyMapSingletonFlag;


CStudyMap::CStudyMap()
{

}

CStudyMap::~CStudyMap()
{

}

std::shared_ptr <IStudyStl> CStudyMap::GetInstance()
{
	std::call_once(g_StudyMapSingletonFlag, [&] {
		g_pStudyMapInstance = std::shared_ptr<IStudyStl>(new CStudyMap());
		});
	return  g_pStudyMapInstance;
}
void CStudyMap::AddElement()
{
	std::cout << "<--------CStudyMap::AddElement-------->" << std::endl;
	std::lock_guard<std::mutex> lock(m_Mutex);
	if (m_iMapTest.size() > 10)
	{
		std::cout << " iCount of AddElement is morn than 10!" << std::endl;
		m_iMapTest.clear();
		return;
	}
	for (int i = 0; i != 5; i++)
	{
		m_iMapTest.insert(std::pair<int, int>(i, i));
		std::cout << "the value of map  is :" << i << std::endl;
	}
}

void CStudyMap::DeleteAllElement()
{
	std::cout << "<--------CStudyMap::DeleteAllElement-------->" << std::endl;
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_iMapTest.clear();
}

void CStudyMap::PrintAllElement()
{
	std::cout << "<--------CStudyMap::PrintAllElemt-------->" << std::endl;
	std::lock_guard<std::mutex> lock(m_Mutex);
	for (auto it = m_iMapTest.begin(); it != m_iMapTest.end(); ++it)
	{
		std::cout << "the list result is: " << (it)->second << std::endl;
	}
}

