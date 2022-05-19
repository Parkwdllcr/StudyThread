
#include "CAddActor.h"
#include "IStudySTL.h"
#include <iostream>

 CAddActor:: CAddActor(IStudyStl*  pStudyStl):
              m_pStudyStl(pStudyStl)
 {

 }
 
 CAddActor:: ~ CAddActor()
 {
	 std::cout << "CAddActor is end!" << std::endl;
 }

void CAddActor::Process()
{
	m_pStudyStl->AddElement();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}
