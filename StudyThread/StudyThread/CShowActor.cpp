
#include"CShowActor.h"
#include "IStudySTL.h"
#include<iostream>

CShowActor:: CShowActor(IStudyStl*  pStudyStl):
              m_pStudyStl(pStudyStl)
 {

 }

 CShowActor:: ~ CShowActor()
{
	std::cout << "CShowActor is end!" << std::endl;
}

 void  CShowActor::Process()
{
     m_pStudyStl->PrintAllElement();
	 std::this_thread::sleep_for(std::chrono::milliseconds(50));
};


