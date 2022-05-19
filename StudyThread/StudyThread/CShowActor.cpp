
#include"CShowActor.h"
#include "IStudySTL.h"
#include<iostream>

CShowActor:: CShowActor(IStudyStl*  pStudyStl):
              m_pStudyStl(pStudyStl),m_Mutex()
 {

 }

 CShowActor:: ~ CShowActor()
{
	std::cout << "CShowActor is end!" << std::endl;
}

 void  CShowActor::Process()
{
	 std::lock_guard<std::mutex> lock(m_Mutex);
     m_pStudyStl->PrintAllElement();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

};
