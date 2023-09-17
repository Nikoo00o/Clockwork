#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <functional>

namespace clockwork {
	namespace utils {
		//true means that you can call the methods start, stop, isRunning and the threadpool can be deleted safely 
		#define THREADPOOL_CHANGERUNSTATUS true
		//true means that you can call the methods isWorking and waitWorking 
		#define THREADPOOL_GETWORKINGSTATUS true

		/*a Threadpool to manage multiple tasks with multiple threads for perfect performance:
		first add some tasks with addTask and then execute them on the threads with flushTasks
		
		you can first queue all your tasks and then flush them afterwards for the threads to work at 100% after you called flush(but the threads wont work during the adding of the tasks before flush) 
		or you can queue your tasks in batches and call flush between them, so the threads work around 60-75%, but they already work during the next adding process
		
		Threadpool, you can set THREADPOOL_CHANGERUNSTATUS and THREADPOOL_GETWORKINGSTATUS to false to improve performance, but 
		THREADPOOL_CHANGERUNSTATUS has to be true, so the threadpool can be deleted safely and stopped/started
		THREADPOOL_GETWORKINGSTATUS has to be true, so the threadpool can be asked if its working */
		class ThreadPool
		{

		private:
			struct ThreadContainer
			{
				std::vector<std::function<void()>> tasks;
			};

			class ThreadWorker
			{

			private:
				friend class ThreadPool;
				ThreadPool* m_pool;
				bool m_running;
				bool m_working;
				std::vector<ThreadContainer*> m_containers;
				std::mutex m_lock;
				std::mutex m_runLock;
				std::thread m_thread;

			public:
				ThreadWorker(ThreadPool* pool) noexcept;
				void running() noexcept;
				~ThreadWorker() noexcept;

			};

		private:
			ThreadContainer** m_containers;
			ThreadWorker** m_workers;
			int m_threadcount;
			int m_currentPos;

		public:

			ThreadPool(unsigned int threadCount = 8, unsigned int threadPriority = 2) noexcept;

			~ThreadPool() noexcept;

			//dont call addtask and flushtasks from multiple threads, only from same thread
			/* you dont have to put in the template parameters, only call the method with a pointer to an object, the memoryadress of a methode of the class of the object(&classname::methodname) and then if available parameters for the method
			*/
			template<typename type, typename ...Args>
			inline void addTask(type* object, void ( type::*method )( Args... ), Args&&... args) noexcept;//as many method parameters as you want 

			void flushTasks() noexcept;

#if THREADPOOL_CHANGERUNSTATUS
			void start() noexcept;

			void stop() noexcept;

			bool isRunning() noexcept;
#endif

#if THREADPOOL_GETWORKINGSTATUS
			bool isWorking() noexcept;

			void waitWorking() noexcept;
#endif

		};

		template<typename type, typename ...Args>
		inline void ThreadPool::addTask(type* object, void ( type::*method )( Args... ), Args&&... args) noexcept
		{
			m_containers[m_currentPos]->tasks.push_back([=] ()
			{
				( object->*method )( std::forward<Args>(args)... );//foward=lvalue, or rvalue arguments depending on function call and therfor template parame args(lvalue reference, or rvalue reference) 
			});
			++m_currentPos;
			if ( m_currentPos == m_threadcount )
				m_currentPos = 0;
		}



		struct str2
		{
			long long into = 10;
			std::mutex muti;
			void testi()
			{
				muti.lock();
				for ( int i = 0; i < 1000; ++i )
				{
					into += 10;
					into -= 10;
					into *= 2;
					into /= 2;
					into++;
					into--;
					into += 2;
					into -= 2;
					into++;
				}
				muti.unlock();
			}
		};

		static void test3()
		{
			ThreadPool pool {8,8};
			str2 ob1;
			str2 ob2;
			str2 ob3;
			str2 ob4;
			str2 ob5;
			str2 ob6;
			str2 ob7;
			str2 ob8;
			std::cout << "START!" << std::endl;
			for ( int i = 0; i < 400000; ++i )
			{
				pool.addTask(&ob1, &str2::testi);
				pool.addTask(&ob2, &str2::testi);
				pool.addTask(&ob3, &str2::testi);
				pool.addTask(&ob4, &str2::testi);
				pool.addTask(&ob5, &str2::testi);
				pool.addTask(&ob6, &str2::testi);
				pool.addTask(&ob7, &str2::testi);
				pool.addTask(&ob8, &str2::testi);
				if ( i % 1000 == 0 || i == 400000 - 1 )
				{
					pool.flushTasks();
					pool.waitWorking();
				}
			}
			std::cout << "STOP!"<< ob1.into<<"  "<<ob8.into<< std::endl;
		}

	}
}