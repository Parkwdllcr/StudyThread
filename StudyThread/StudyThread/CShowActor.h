#pragma once 

#include "CThread.h"
#include "IStudyStl.h"
#include "CSemaphore.h"

class IStudyStl;
class CShowActor:public CThread
{
public:
     CShowActor(IStudyStl*  pStudyStl);
     ~CShowActor();
public:
    void Process();
	void TerminateThread();
private:
    IStudyStl*      m_pStudyStl;
	CSemaphore      m_Semaphore;
};
