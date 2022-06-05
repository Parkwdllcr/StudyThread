#pragma once
#include "Diana.h"
#include <assert.h>
#include <functional>
namespace Diana
{
	using WorkItem = std::function<void()>;

	//简易多线程多任务队列线程池，使用SafeQueue线程安全队列
	class MultiplePool
	{
	public:
		explicit MultiplePool(size_t iThreadNum = std::thread::hardware_concurrency())
			:m_queue(iThreadNum), m_iThreadNum(iThreadNum)
		{
			auto worker = [this](size_t id)
			{
				while (true)
				{
					WorkItem task{};
					if (!m_queue[id].Pop(task))
					{
						break;
					}
					if (task)
					{
						task();
					}
				}
			};

			m_workers.reserve(m_iThreadNum);
			for (size_t i = 0;i<m_iThreadNum;++i)
			{
				m_workers.emplace_back(worker, i);
			}
		}
		int ScheduleById(WorkItem Fn,size_t id = -1)
		{
			if ( nullptr == Fn)
			{
				return -1;
			}

			if (id == -1)
			{
				id = rand() % m_iThreadNum;//随机插入到一个线程的任务队列中
				m_queue[id].Push(std::move(Fn));
			}
			else
			{
				assert(id < m_iThreadNum);//插入指定线程的任务队列
				m_queue[id].Push(std::move(Fn));
			}

			return 0;
		}

		~MultiplePool()
		{
			for (auto& queue:m_queue)
			{
				queue.Stop();//停止每一个任务队列
			}
			for (auto& worker:m_workers)
			{
				worker.join();//阻塞，等待每一个线程执行结束
			}
		}
	private:
		std::vector<Diana::SafeQueue<WorkItem>>      m_queue;//每个线程对应一个任务队列
		size_t                                       m_iThreadNum;
		std::vector<std::thread>                     m_workers;
	
	};
}