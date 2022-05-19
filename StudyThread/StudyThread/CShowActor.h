#pragma once 

#include "CThread.h"
#include "IStudyStl.h"

class IStudyStl;
class CShowActor:public CThread
{
public:
     CShowActor(IStudyStl*  pStudyStl);
     ~CShowActor();
public:
    void Process();
private:
    IStudyStl*      m_pStudyStl;
	std::mutex      m_Mutex;
};
