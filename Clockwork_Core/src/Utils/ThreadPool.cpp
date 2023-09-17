#include "ThreadPool.h"

namespace clockwork {
	namespace utils {

		ThreadPool::ThreadWorker::ThreadWorker(ThreadPool* pool) noexcept
			: m_pool(pool),
#if THREADPOOL_CHANGERUNSTATUS
			m_running(true),
#endif
#if THREADPOOL_GETWORKINGSTATUS
			m_working(false),
#endif
			m_thread(&ThreadWorker::running, this)
		{
			m_containers.reserve(20);
		}

		ThreadPool::ThreadWorker::~ThreadWorker() noexcept
		{
#if THREADPOOL_CHANGERUNSTATUS
			m_runLock.lock();
			m_running = false;
			for ( int i = 0; i < m_containers.size(); ++i )
			{
				delete m_containers[i];
			}
			m_runLock.unlock();
			m_thread.join();
#endif
		}

		void ThreadPool::ThreadWorker::running() noexcept
		{
			while ( true )
			{
#if THREADPOOL_CHANGERUNSTATUS
				m_runLock.lock();
				if ( m_running )
				{
#endif
					m_lock.lock();
					if ( !m_containers.empty() )
					{
						ThreadContainer* container = m_containers.front();
						m_containers.erase(m_containers.begin());
#if THREADPOOL_GETWORKINGSTATUS
						m_working = true;
#endif
						m_lock.unlock();
						for ( unsigned int i = 0; i < container->tasks.size(); ++i )
						{
							container->tasks.at(i)( );
						}
						delete container;
					}
					else
					{
#if THREADPOOL_GETWORKINGSTATUS
						m_working = false;
#endif
						m_lock.unlock();
						std::this_thread::sleep_for(std::chrono::duration<double>(0.0001));
					}
#if THREADPOOL_CHANGERUNSTATUS
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::duration<double>(0.0001));
				}
				m_runLock.unlock();
#endif
			}
		}

		ThreadPool::ThreadPool(unsigned int threadCount, unsigned int threadPriority) noexcept
			: m_threadcount(threadCount), m_currentPos(0)
		{
			m_containers = new ThreadContainer*[threadCount];
			m_workers = new ThreadWorker*[threadCount];

			for ( unsigned int i = 0; i < m_threadcount; ++i )
			{
				m_containers[i] = new ThreadContainer {};
			}
			for ( unsigned int i = 0; i < m_threadcount; ++i )
			{
				m_workers[i] = new ThreadWorker { this };
			}
		}

		ThreadPool::~ThreadPool() noexcept
		{
			for ( unsigned int i = 0; i < m_threadcount; ++i )
			{
				delete m_containers[i];
			}
			for ( unsigned int i = 0; i < m_threadcount; ++i )
			{
				delete m_workers[i];
			}
			delete m_containers;
			delete m_workers;
		}

		void ThreadPool::flushTasks() noexcept
		{
			ThreadContainer* container;
			ThreadWorker* worker;
			for ( int i = 0; i < m_threadcount; ++i )
			{
				container = m_containers[i];
				m_containers[i] = new ThreadContainer {};
				worker = m_workers[i];
				worker->m_lock.lock();
				worker->m_containers.push_back(container);
#if THREADPOOL_GETWORKINGSTATUS
				worker->m_working = true;
#endif
				worker->m_lock.unlock();
			}
		}


#if THREADPOOL_CHANGERUNSTATUS
		void ThreadPool::start() noexcept
		{
			for ( int i = 0; i < m_threadcount; ++i )
			{
				ThreadWorker* worker = m_workers[i];
				worker->m_runLock.lock();
				worker->m_running = true;
				worker->m_runLock.unlock();
			}
		}

		void ThreadPool::stop() noexcept
		{
			for ( int i = 0; i < m_threadcount; ++i )
			{
				ThreadWorker* worker = m_workers[i];
				worker->m_runLock.lock();
				worker->m_running = false;
				worker->m_runLock.unlock();
			}
		}

		bool ThreadPool::isRunning() noexcept
		{
			return true;
		}
#endif

#if THREADPOOL_GETWORKINGSTATUS
		bool ThreadPool::isWorking() noexcept
		{
			ThreadWorker* worker;
			for ( unsigned int i = 0; i < m_threadcount; ++i )
			{
				worker = m_workers[i];
				worker->m_lock.lock();
				if ( worker->m_working )
				{
					worker->m_lock.unlock();
					return true;
				}
				worker->m_lock.unlock();
			}
			return false;
		}

		void ThreadPool::waitWorking() noexcept
		{
			while ( isWorking() )
			{
				std::this_thread::sleep_for(std::chrono::duration<double>(0.0001));
			}
		}
#endif



	}
}