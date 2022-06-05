#pragma once
#include <condition_variable>
#include<queue>
#include<mutex>
#include<functional>
#include "Diana.h"

namespace Diana
{
	using WorkItem = std::function<void()>;
	// * 简易多线程单任务队列线程池，使用SafeQueue线程安全队列。
	class Simplepool {
		explicit Simplepool(size_t iThreads = std::thread::hardware_concurrency())
		{
			for (size_t i = 0;i<iThreads;++i)
			{
				m_Workers.emplace_back([this]
					{
						for (;;)
						{
							std::function<void()> task;
							if (!m_queue.Pop(task))
							{
								return;
							}
							if (task)
							{
								task();
							}
						}
					});
			}
		}
		void Enqueue(WorkItem item)
		{
			m_queue.Push(std::move(item));
		}
		~Simplepool() {
			m_queue.Stop();
			for (auto& thd:m_Workers)
			{
				thd.join();
			}
		}
	
	private:
		SafeQueue<WorkItem>   m_queue;
		std::vector<std::thread> m_Workers;
	};
}
