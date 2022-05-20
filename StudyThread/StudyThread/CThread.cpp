#include "CThread.h"
#include <iostream>

using namespace std;

CThread::CThread()
	: m_pThread(nullptr),
	m_bPauseFlag(false),
	m_bStopFlag(false),
	m_enState(Stoped)
{

}

CThread::~CThread()
{
	Stop();
}


CThread::State CThread::GetState() const
{
	return m_enState;
}

void CThread::Start()
{
	if (m_pThread == nullptr)
	{
		m_pThread = new thread(&CThread::Run, this);
		m_bPauseFlag = false;
		m_bStopFlag = false;
		m_enState = Running;
	}
}

void CThread::Stop()
{
	if (m_pThread != nullptr)
	{
		m_bPauseFlag = false;
		m_bStopFlag = true;
		if (m_enState == Paused)
		{
			m_Condition.notify_all();  // Notify one waiting thread, if there is one.
		}
		m_pThread->join(); // wait for thread finished
		m_enState = Stoped;
		delete m_pThread;
		m_pThread = nullptr;
	}
}

void CThread::Pause()
{
	if (m_pThread != nullptr)
	{
		m_bPauseFlag = true;
		m_enState = Paused;
	}
}

void CThread::Resume()
{
	if (m_pThread != nullptr)
	{
		m_bPauseFlag = false;
		m_Condition.notify_all();
		m_enState = Running;
	}
}

void CThread::Run()
{
	std::cout << "enter thread:" << this_thread::get_id() << std::endl;

	while (!m_bStopFlag)
	{
		Process();
		if (m_bPauseFlag)
		{
			unique_lock<mutex> locker(m_Mutex);
			while (m_bPauseFlag)
			{
				m_Condition.wait(locker); // Unlock _mutex and wait to be notified
			}
			locker.unlock();
		}
	}
	m_bPauseFlag = false;
	m_bStopFlag = false;
	cout << "exit thread:" << this_thread::get_id() << endl;
}
