// StudyThread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "CThread.h"
#include <string>
#include "CAddActor.h"
#include "CDeleteActor.h"
#include "CShowActor.h"
#include "CStudyList.h"
#include"ThreadPool.h"



void func()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "worker thread ID:" << std::this_thread::get_id() << std::endl;

}
int main()
{
	//std::shared_ptr<IStudyStl> pStudylist = CStudyList::GetInstance();
	//IStudyStl* pList = pStudylist.get();

	//std::shared_ptr<CAddActor> pAddThread(new(std::nothrow) CAddActor(pList));
	//std::shared_ptr<CDeleteActor> pDeletThread(new(std::nothrow) CDeleteActor(pList));
	//std::shared_ptr<CShowActor> pShowThread(new(std::nothrow) CShowActor(pList));

	//pAddThread->Start();
	//std::this_thread::sleep_for(std::chrono::milliseconds(50));
	//pAddThread->Stop();

	//pShowThread->Start();
	//std::this_thread::sleep_for(std::chrono::milliseconds(1));

	//pDeletThread->Start();
	//std::this_thread::sleep_for(std::chrono::milliseconds(1));

	////pShowThread->Start();
	//std::this_thread::sleep_for(std::chrono::milliseconds(1));

	//pDeletThread->Stop();
	//pShowThread->Stop();


	//ThreadPool pool(4);

	//// enqueue and store future
	//auto result = pool.enqueue([](int answer) { return answer; }, 42);

	//// get result from future, print 42
	//std::cout << result.get() << std::endl;

	ThreadPool pool(4);
	while (1)
	{
		pool.enqueue(func);
	}

}

