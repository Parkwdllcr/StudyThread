#pragma once
#include "IStudySTL.h"
#include<mutex>
#include<map>

class CStudyMap :
    public IStudyStl
{
public:
	static std::shared_ptr <IStudyStl> GetInstance();
	~CStudyMap() ;
public:
	virtual  void AddElement();
	virtual  void DeleteAllElement();
	virtual  void PrintAllElement();
private:
	CStudyMap() ;
private:
	std::mutex                        m_Mutex;
	std::map<int,int>                 m_iMapTest;
};

