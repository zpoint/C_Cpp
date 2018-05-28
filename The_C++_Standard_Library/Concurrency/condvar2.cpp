#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>
#include <iostream>
#include <queue>

std::queue<int> queue;
std::mutex queueMutex;
std::condition_variable queueCondVar;

void provider(int val)
{
		// push different values (val til val + 5 with timeouts of val milliseconds into the queue)
		for (int i = 0; i < 6; ++i)
		{
				std::lock_guard<std::mutex> lg(queueMutex);
				queue.push(val + i);
		} // release lock
		queueCondVar.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(val));
}

void consumer(int num)
{
		// pop values if avaliable (num identifies the consumer)
		while (true)
		{
				int val;
				{
						std::unique_lock<std::mutex> ul(queueMutex);
						queueCondVar.wait(ul, [] { return !queue.empty(); });
						// std::cout << "wait return: " << num << std::endl;
						val = queue.front();
						queue.pop();
						std::cout << "consumer " << num << ": " << val << std::endl;
				} // release lock
		}
}

int main()
{
		// start three providers for values 100+, 300+ and 500+
		std::future<void> p1 = std::async(std::launch::async, provider, 100);
		std::future<void> p2 = std::async(std::launch::async, provider, 300);
		std::future<void> p3 = std::async(std::launch::async, provider, 500);

		// start two consumers printing the values
		std::future<void> c1 = std::async(std::launch::async, consumer, 1);
		std::future<void> c2 = std::async(std::launch::async, consumer, 2);
		return 0;
}
