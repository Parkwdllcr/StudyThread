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
#include"Diana.h"
#include"SimplePool.h"
#include"MultiplePool.h"



void func()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "worker thread ID:" << std::this_thread::get_id() << std::endl;

}
void test_thread_pool() {
	std::cout << "test_thread_pool()" << std::endl;
	Diana::ThreadPool threadPool;
	threadPool.enqueue([] { std::cout << "hello\n"; });
	auto future = threadPool.enqueue([](std::string str) { return "hello" + str; }, "world");
	std::cout << future.get() << std::endl;
}
​
std::string funA(std::string str) 
{
	return "hello" + str;
}
​
void test_simple_thread_pool() {
	std::cout << "test_simple_thread_pool()" << std::endl;
	Diana::SimplePool threadPool;
	threadPool.enqueue([] { std::cout << "hello\n"; });
	// * 此处必须使用shared_ptr进行包装，
	// * 否则在std::function<void()>中会尝试生成std::packaged_task的拷贝构造函数，
	// ! std::packaged_task禁止拷贝操作
	auto task = std::make_shared<std::packaged_task<std::string()>>(std::bind(funA, "world"));
	std::future<std::string> res = task->get_future();
	threadPool.enqueue([task = std::move(task)]{ (*task)(); });
	// ! 以下实现方法是错误的
	//  auto task = std::packaged_task<std::string()>(std::bind(funA, "world"));
	//  std::future<std::string> res = task.get_future();
	//  threadPool.enqueue(std::move(task));
	std::cout << res.get() << std::endl;
}
​
void test_multiple_thread_pool() {
	std::cout << "test_multiple_thread_pool" << std::endl;
	Diana::MultiplePool threadPool;
	threadPool.schedule_by_id([] { std::cout << "hello\n"; });
	auto task = std::make_shared<std::packaged_task<std::string()>>(std::bind(funA, "world"));
	std::future<std::string> res = task->get_future();
	threadPool.schedule_by_id([task = std::move(task)]{ (*task)(); });
	std::cout << res.get() << std::endl;
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

