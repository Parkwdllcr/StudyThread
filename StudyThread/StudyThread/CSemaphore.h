#pragma once

#include <mutex>
#include <condition_variable>
#include <cassert>
#include <chrono>
#include <iostream>


/**
 * semaphore类似于一个信号量类，利用mutex和condition_variable来实现
 */
class CSemaphore
{
public:
     CSemaphore(std::string strName, unsigned long ulCount = 0);
	 CSemaphore();
	~CSemaphore();
	//阻止拷贝
	CSemaphore(const CSemaphore&) = delete;
	//阻止赋值
	CSemaphore& operator=(const CSemaphore&) = delete;

public:
	bool Wait(int64_t iTimeOut);
	void Trigger();

    void TriggerAll();

public:
    std::string GetMyName();

private:
    std::string    m_strName;
    unsigned long m_ulCount;                             //等待线程数量
    std::mutex  m_mutex;                      //互斥锁
    std::condition_variable m_condition;   //条件变量
};


  
