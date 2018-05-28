#include <atomic> // for atomics
#include <future> // for async() and futures
#include <thread> // for this_thread
#include <chrono> // for durations
#include <iostream>

long data;
std::atomic<bool> readyFlag(false);

void provider()
{
		// after reading a character
		std::cout << "<return>" << std::endl;
		std::cin.get();

		// provide some data
		data = 42;

		// and signal readiness
		readyFlag.store(true);
}

void consumer()
{
		// wait for readiness and do something else
		while (!readyFlag.load())
		{
				std::cout.put('.').flush();
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		// and process provided data
		std::cout << "\nvalye: " << data << std::endl;
}

int main()
{
		// start provider and consumer
		std::future<void> p = std::async(std::launch::async, provider);
		std::future<void> c = std::async(std::launch::async, consumer);
		return 0;
}
