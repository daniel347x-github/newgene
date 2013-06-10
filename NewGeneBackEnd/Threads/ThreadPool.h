#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <memory>
#include <vector>
#ifndef Q_MOC_RUN
#	include <boost/asio/io_service.hpp>
#	include <boost/thread.hpp>
#endif


template<typename WORKER_THREAD_CLASS>
class ThreadPool
{

public:

	typedef std::pair<std::shared_ptr<boost::thread>, std::shared_ptr<WORKER_THREAD_CLASS>> thread_worker; 

	ThreadPool(boost::asio::io_service & work_service, int const nThreads)
	{
		for(int n=0; n<nThreads; ++n)
		{
			auto worker = std::make_shared<WORKER_THREAD_CLASS>(work_service);
			threads.push_back(std::make_pair(std::make_shared<boost::thread>(boost::bind(&WORKER_THREAD_CLASS::operator(), worker)), worker));
		}
	}

	~ThreadPool()
	{
		for_each(threads.begin(), threads.end(), [](thread_worker & thread){
			thread.second->stop();
			thread.first->join();
		});
	}

protected:

	std::vector<thread_worker> threads;

};

#endif
