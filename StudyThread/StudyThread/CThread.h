#pragma once

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

class CThread
{
public:
	CThread();
	virtual ~CThread();

	enum State
	{
		Stoped,     ///<停止状态，包括从未启动过和启动后被停止
		Running,    ///<运行状态
		Paused      ///<暂停状态
	};
	State GetState() const;

	void Start();
	void Stop();
	void Pause();
	void Resume();

protected:
	virtual void Process() = 0;

private:
	void Run();

private:
	std::thread*                    m_pThread;
	std::mutex                      m_Mutex;
	std::condition_variable         m_Condition;
	std::atomic_bool                m_bPauseFlag;   ///<暂停标识
	std::atomic_bool                m_bStopFlag;   ///<停止标识
	State                           m_enState;
};



