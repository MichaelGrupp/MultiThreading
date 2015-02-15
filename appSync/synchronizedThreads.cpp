//based on: http://www.highscore.de/cpp/boost/multithreading.html

#include <boost/thread.hpp> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

//create a mutex
boost::mutex mutex;
//this condition variable will be used for notifications of the threads
boost::condition_variable_any cond;
//shared resource
std::vector<int> random_numbers;

void fill()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	for (int i = 0; i < 3; ++i)
	{
		//lock the mutex uniquely
		boost::unique_lock<boost::mutex> lock(mutex);
		random_numbers.push_back(std::rand());
		//notify threads waiting for condition variable notification
		cond.notify_all();
		//wait for another thread to call cond.notify_all() and free mutex
		cond.wait(mutex);
	}
}

void print()
{
	std::size_t next_size = 1;
	for (int i = 0; i < 3; ++i)
	{
		//lock the mutex uniquely
		boost::unique_lock<boost::mutex> lock(mutex);
		while (random_numbers.size() != next_size)
			cond.wait(mutex);
		std::cout << random_numbers.back() << std::endl;
		++next_size;
		//notify waiting threads
		cond.notify_all();
	}
}

int main()
{
	boost::thread t1(fill);
	boost::thread t2(print);
	t1.join();
	t2.join();
	std::cin.get();
}