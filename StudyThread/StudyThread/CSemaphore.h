#pragma once

#include <mutex>
#include <condition_variable>
#include <cassert>
#include <chrono>
#include <iostream>


/**
 * semaphore������һ���ź����࣬����mutex��condition_variable��ʵ��
 */
class CSemaphore
{
public:
     CSemaphore(std::string strName, unsigned long ulCount = 0);
	 CSemaphore();
	~CSemaphore();
	//��ֹ����
	CSemaphore(const CSemaphore&) = delete;
	//��ֹ��ֵ
	CSemaphore& operator=(const CSemaphore&) = delete;

public:
	bool Wait(int64_t iTimeOut);
	void Trigger();

    void TriggerAll();

public:
    std::string GetMyName();

private:
    std::string    m_strName;
    unsigned long m_ulCount;                             //�ȴ��߳�����
    std::mutex  m_mutex;                      //������
    std::condition_variable m_condition;   //��������
};


  
