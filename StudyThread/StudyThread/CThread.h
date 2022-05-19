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
		Stoped,     ///<ֹͣ״̬��������δ��������������ֹͣ
		Running,    ///<����״̬
		Paused      ///<��ͣ״̬
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
	std::atomic_bool                m_bPauseFlag;   ///<��ͣ��ʶ
	std::atomic_bool                m_bStopFlag;   ///<ֹͣ��ʶ
	State                           m_enState;
};



