#pragma once 
#include "CThread.h"

class IStudyStl;
class CDeleteActor:public CThread
{
public:
     CDeleteActor(IStudyStl*  pStudyStl);
     ~CDeleteActor();
public:
    void Process();
private:
    IStudyStl*      m_pStudyStl;
	std::mutex      m_Mutex;
};
