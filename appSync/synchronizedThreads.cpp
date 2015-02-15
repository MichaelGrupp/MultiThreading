//based on: http://www.highscore.de/cpp/boost/multithreading.html

#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds)
{
	boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

//create a mutex
boost::mutex mutex;

void thread()
{
	for (int i = 0; i < 5; ++i)
	{
		wait(1);
		//if a mutex is locked, a section can only be used by a single thread that owns the mutex
		mutex.lock();
		std::cout << "Thread " << boost::this_thread::get_id() << ": " << i << std::endl;
		mutex.unlock();
	}
}

int main()
{
	//calling two same threads doesn't lead to to conflicts because 
	boost::thread t1(thread);
	boost::thread t2(thread);
	t1.join();
	t2.join();
}