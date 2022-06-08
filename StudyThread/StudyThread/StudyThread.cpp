// StudyThread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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
#include <iostream>
#include"boost/thread/thread_pool.hpp"
#include <boost/asio.hpp>
#include<boost/bind.hpp>
#include <boost/thread.hpp>
#include<mutex>
#include <condition_variable>

std::mutex m_mutex;
void func()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "worker thread ID:" << std::this_thread::get_id() << std::endl;

}
//void test_thread_pool() {
//	std::cout << "test_thread_pool()" << std::endl;
//	Diana::ThreadPo threadPool;
//	threadPool.enqueue([] { std::cout << "hello\n"; });
//	auto future = threadPool.enqueue([](std::string str) { return "hello" + str; }, "world");
//	std::cout << future.get() << std::endl;
//}

//std::string funA(std::string str)
//{
//	return "hello" + str;
//}
//
//void test_simple_thread_pool() 
//{
//	std::cout << "test_simple_thread_pool()" << std::endl;
//	Diana::SimplePool threadPool;
//	threadPool.Enqueue([] { std::cout << "hello\n"; });
//	// * 此处必须使用shared_ptr进行包装，
//	// * 否则在std::function<void()>中会尝试生成std::packaged_task的拷贝构造函数，
//	// ! std::packaged_task禁止拷贝操作
//	auto task = std::make_shared<std::packaged_task<std::string()>>(std::bind(funA, "world"));
//	std::future<std::string> res = task->get_future();
//	threadPool.Enqueue([task = std::move(task)]{ (*task)(); });
//	// ! 以下实现方法是错误的
//	//  auto task = std::packaged_task<std::string()>(std::bind(funA, "world"));
//	//  std::future<std::string> res = task.get_future();
//	//  threadPool.enqueue(std::move(task));
//	std::cout << res.get() << std::endl;
//}
//
//void test_multiple_thread_pool() 
//{
//	std::cout << "test_multiple_thread_pool" << std::endl;
//	Diana::MultiplePool threadPool;
//	threadPool.ScheduleById([] { std::cout << "hello\n"; });
//	auto task = std::make_shared<std::packaged_task<std::string()>>(std::bind(funA, "world"));
//	std::future<std::string> res = task->get_future();
//	threadPool.ScheduleById([task = std::move(task)]{ (*task)(); });
//	std::cout << res.get() << std::endl;
//}


const int iCount = 1000;
std::atomic<int> sum = 0;
void Test()
{
	/*SYSTEMTIME systemtime;
	 GetLocalTime(&systemtime);
	 std::cout << "Start 秒Second :"<<systemtime.wSecond <<std::endl; 
	 std::cout<<  "Start 毫秒  :"<<systemtime.wMilliseconds << std::endl;*/
	 for (int i = 0;i != 1000; ++i)
	 {
		//std::lock_guard<std::mutex> lock(m_mutex);
		/*m_mutex.lock();*/
		 sum += 1;
		 std::cout << "thread Id:" << boost::this_thread::get_id() << ", Sum =" << sum << std::endl;
		/* GetLocalTime(&systemtime);
		 std::cout << "end systemtime.wSecond :" << systemtime.wSecond << std::endl;
		 std::cout << "end systemtime.wMilliseconds  :" << systemtime.wMilliseconds << std::endl;
		 m_mutex.unlock();*/
	 }
	 /*GetLocalTime(&systemtime);
	 std::cout << "end2 秒 :" << systemtime.wSecond << std::endl;
	 std::cout << "end2 毫秒:" << systemtime.wMilliseconds << std::endl;*/
}
void FirstTask()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	for (int i =1;i!= iCount;++i)
	{
		std::cout << std::this_thread::get_id()<< ": " << i << std::endl;
	}
}

void SecodTask(std::string str)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	for (int i = 0;i != iCount;++i)
	{
		std::cout << std::this_thread::get_id() <<": "<< i << std::endl;
	}
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

	//ThreadPool pool(4);
	//while (1)
	//{
	//	pool.enqueue(func);
	//}

	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
    std::cout << "start systemtime.wSecond :" << systemtime.wSecond << std::endl;
	std::cout << "start systemtime.wMilliseconds  :" << systemtime.wMilliseconds << std::endl;
	boost::asio::thread_pool pool(2);
	boost::asio::post(pool, FirstTask);
	boost::asio::post(pool, boost::bind(SecodTask, "lcr"));
	pool.join();
	GetLocalTime(&systemtime);
	std::cout << "end systemtime.wSecond :" << systemtime.wSecond << std::endl;
	std::cout << "end systemtime.wMilliseconds  :" << systemtime.wMilliseconds << std::endl;

	int iTemp = 0;
	for (int i =0;i!= 2*iCount;++i)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		std::cout << std::this_thread::get_id() << ": " << i << std::endl;
	}

	GetLocalTime(&systemtime);
	std::cout << "结束 systemtime.wSecond :" << systemtime.wSecond << std::endl;
	std::cout << "结束 systemtime.wMilliseconds  :" << systemtime.wMilliseconds << std::endl;
	return 0;
}

