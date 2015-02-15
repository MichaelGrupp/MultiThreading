//based on: http://www.highscore.de/cpp/boost/multithreading.html

#include <boost/thread.hpp> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

#include <boost/thread.hpp> 
#include <iostream> 

void wait(int seconds)
{
	boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

void thread()
{
	for (int i = 0; i < 5; ++i)
	{
		wait(1);
		std::cout << i << std::endl;
	}
}

int main()
{
	//create a boost thread == thread constructor with a function as parameter
	boost::thread t(thread);

	//join connects main and the t thread, so it shuts down only when t as finished 
	t.join();
}