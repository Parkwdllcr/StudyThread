
#include "CAddActor.h"
#include "IStudySTL.h"
#include <iostream>

 CAddActor:: CAddActor(IStudyStl*  pStudyStl):
              m_pStudyStl(pStudyStl),m_Mutex()
 {

 }
 
 CAddActor:: ~ CAddActor()
 {
	 std::cout << "CAddActor is end!" << std::endl;
 }

void CAddActor::Process()
{
	std::lock_guard<std::mutex> lock(m_Mutex);
	m_pStudyStl->AddElement();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}
