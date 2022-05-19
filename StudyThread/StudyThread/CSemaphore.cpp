#include "CSemaphore.h"

CSemaphore::CSemaphore(std::string strName, unsigned long ulCount /*= 0*/)
    :m_ulCount(ulCount),m_strName(strName)
{

}

CSemaphore::CSemaphore()
{

}

CSemaphore::~CSemaphore()
{

}

bool CSemaphore::Wait(int64_t iTimeOut)
{
	try
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		switch (iTimeOut)
		{
		case -1://资源不足，永久等待
			m_condition.wait(lock); // 阻塞
			break;
		case 0://不等待
			break;
		default:
			std::cv_status status = m_condition.wait_for(lock, std::chrono::milliseconds(iTimeOut));
			if (status == std::cv_status::timeout)   // 超时
			{
				std::cout << m_strName + ":timeout" << std::endl;
				m_ulCount = 0;
				m_condition.notify_all();//唤醒所有阻塞线程
			}
			break;
		}
		--m_ulCount;
		return true;

	}
	catch (const std::exception&)
	{
		std::cout << "CSemaphore::Wait Get a Unknow Error!" << std::endl;
		return false;
	}
    
}

void CSemaphore::Trigger()
{
	try
	{
		if ((++m_ulCount) <= 0)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_condition.notify_one();
		}
	}
	catch (const std::exception&)
	{
		std::cout << "CSemaphore::Trgger Get a Unknow Error!" << std::endl;
	}
	
	
}

void CSemaphore::TriggerAll()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	while (++m_ulCount <= 0) {
		m_condition.notify_one();
	}
	m_ulCount = 0;
}

std::string CSemaphore::GetMyName()
{
    return m_strName;
}
