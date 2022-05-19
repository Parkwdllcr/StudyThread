#pragma once 
#include "CThread.h"


class IStudyStl;
class CAddActor:public CThread
{
public:
     CAddActor(IStudyStl*  pStudyStl);
     ~CAddActor();
public:
    void Process();
private:
    IStudyStl*                     m_pStudyStl;
	std::mutex                     m_Mutex;
};
