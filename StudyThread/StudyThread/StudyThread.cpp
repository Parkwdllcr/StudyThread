// StudyThread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "CThread.h"
#include <string>
#include "CAddActor.h"
#include "CDeleteActor.h"
#include "CShowActor.h"
#include "CStudyList.h"

int main()
{
	//std::shared_ptr<CStudyList> ptrStudyList(new CStudyList);
//IStudyStl pStudyList = CStudyList::GetInstance();

	std::shared_ptr<IStudyStl> pStudylist = CStudyList::GetInstance();
	IStudyStl* pList = pStudylist.get();

	std::shared_ptr<CAddActor> pAddThread(new(std::nothrow) CAddActor(pList));
	pAddThread->Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	std::shared_ptr<CDeleteActor> pDeletThread(new(std::nothrow) CDeleteActor(pList));
	pDeletThread->Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	std::shared_ptr<CShowActor> pShowThread(new(std::nothrow) CShowActor(pList));
	pShowThread->Start();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));

	pAddThread->Stop();
	pDeletThread->Stop();
	pShowThread->Stop();
}

