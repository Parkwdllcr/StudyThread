#pragma once
#include "Diana.h"
#include <assert.h>
#include <functional>
namespace Diana
{
	using WorkItem = std::function<void()>;

	//���׶��̶߳���������̳߳أ�ʹ��SafeQueue�̰߳�ȫ����
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
				id = rand() % m_iThreadNum;//������뵽һ���̵߳����������
				m_queue[id].Push(std::move(Fn));
			}
			else
			{
				assert(id < m_iThreadNum);//����ָ���̵߳��������
				m_queue[id].Push(std::move(Fn));
			}

			return 0;
		}

		~MultiplePool()
		{
			for (auto& queue:m_queue)
			{
				queue.Stop();//ֹͣÿһ���������
			}
			for (auto& worker:m_workers)
			{
				worker.join();//�������ȴ�ÿһ���߳�ִ�н���
			}
		}
	private:
		std::vector<Diana::SafeQueue<WorkItem>>      m_queue;//ÿ���̶߳�Ӧһ���������
		size_t                                       m_iThreadNum;
		std::vector<std::thread>                     m_workers;
	
	};
}