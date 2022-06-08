#pragma once
//#include <condition_variable>
//#include<queue>
//#include<mutex>
//namespace Diana
//{
//	template <typename T>
//	class SafeQueue 
//	{
//	public:
//		void Push(const T& iTem)
//		{
//			{
//				std::scoped_lock lock(m_mutex);
//				m_queue.push(iTem);
//			}
//			m_condition.notify_one();
//		}
//		bool Pop(T& item)
//		{
//			std::unique_lock   lock(m_mutex);
//			m_condition.wait(lock, [&]()
//				{
//					return !m_queue.empty() || m_bStop;
//				});
//
//			if (m_queue.empty())
//			{
//				return false;
//			}
//
//			item = std::move(m_queue.front());
//			m_queue.pop();
//			return true;
//		}
//		std::size_t Size() const
//		{
//			std::scoped_lock lock(m_mutex);
//			return m_queue.size();
//		}
//		bool Empty() const 
//		{
//			std::scoped_lock lock(m_mutex);
//			return m_queue.empty();
//		}
//		void Stop()
//		{
//			{
//				std::scoped_lock lock(m_mutex);
//				m_bStop = true;
//			}
//			m_condition.notify_all();
//		}
//	private:
//		std::condition_variable m_condition;
//		mutable std::mutex      m_mutex;
//		std::queue<T>           m_queue;
//		bool                    m_bStop = false;
//	};//namespace Diana
//
//};
