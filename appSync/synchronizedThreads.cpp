//based on: http://www.highscore.de/cpp/boost/multithreading.html

#include <boost/thread.hpp> 
#include <iostream> 
#include <vector> 
#include <cstdlib> 
#include <ctime> 

void wait(int seconds)
{
	boost::this_thread::sleep(boost::posix_time::seconds(seconds));
}

boost::shared_mutex mutex;

//this is the shared resource
std::vector<int> random_numbers;

//fill() reads and writes to the shared resource --> use unique_lock
void fill()
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	for (int i = 0; i < 3; ++i)
	{
		boost::unique_lock<boost::shared_mutex> lock(mutex);
		random_numbers.push_back(std::rand());
		lock.unlock();
		wait(1);
	}
}

//print() reads only from the shared resource --> use shared_lock
void print()
{
	for (int i = 0; i < 3; ++i)
	{
		wait(1);
		boost::shared_lock<boost::shared_mutex> lock(mutex);
		std::cout << boost::this_thread::get_id() << "  " << random_numbers.back() << std::endl;
	}
}

int sum = 0;

//count() reads only from the shared resource --> use shared_lock
void count()
{
	for (int i = 0; i < 3; ++i)
	{
		wait(1);
		boost::shared_lock<boost::shared_mutex> lock(mutex);
		sum += random_numbers.back();
	}
}

int main()
{
	boost::thread t1(fill);
	boost::thread t2(print);
	boost::thread t3(count);
	t1.join();
	t2.join();
	t3.join();
	std::cout << "Summe: " << sum << std::endl;
	
	std::cin.get();
}