#pragma once
#include "IStudySTL.h"
#include<mutex>
#include<list>

class CStudyList :
    public IStudyStl
{
public:
	static std::shared_ptr <IStudyStl> GetInstance();
	~CStudyList();
public:
	virtual  void AddElement();
	virtual  void DeleteAllElement();
	virtual  void PrintAllElement();
private:
	CStudyList() ;
private:
	std::mutex                         m_Mutex;
	std::list<int>                     m_iListTest;
};






