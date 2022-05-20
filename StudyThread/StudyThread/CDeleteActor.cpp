#include"CDeleteActor.h"
#include<iostream>
#include "IStudySTL.h"



 CDeleteActor::CDeleteActor(IStudyStl*  pStudyStl):
              m_pStudyStl(pStudyStl)
 {

 }

CDeleteActor:: ~CDeleteActor()
{
    std::cout << "CDeleteActor is end!" << std::endl;
}

void CDeleteActor::Process()
{
    m_pStudyStl->DeleteAllElement();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
};
