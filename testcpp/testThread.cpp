#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <thread>
#include <vector>
#include <utility>
#include <chrono>
#include <functional>
#include <atomic>
#include <mutex>

using std::thread;

struct Counter
{
	std::mutex mutex;
	int value;
	Counter():value(0) {}

	//木有互斥锁的时候，结果是不确定的
	void increment(){
		mutex.lock();
		++value;
		mutex.unlock();
	}	

	void decrement(){
		mutex.lock();
		--value;
		mutex.unlock();
	}
};

void testCount()
{
	std::cout << "start testCount" << std::endl;
	Counter counter;
	std::vector<thread> threads;
	for (int i = 0; i < 5; ++i)
	{
		threads.push_back(std::thread([&](){
			for (int i = 0; i < 10000; ++i)
			{
				counter.increment();
			}
		}));
		/* code */
	}


	for(auto &thread: threads){
		thread.join();
	}
	std::cout << counter.value << std::endl;
	std::cout << "end testCount" << std::endl;
}

void f1(int n ){
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "Thread:" << n << "executing\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		/* code */
	}
}

void f2(int n ){
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "Thread 2 executing\n";
		++n;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		/* code */
	}
}

void testThread(){
	std::cout << "start testThread" << std::endl;
	int n = 0;
	std::thread t1;
	std::thread t2(f1, n+1);
	std::thread t3(f2, std::ref(n));
	std::thread t4(std::move(t3));
	t2.join();
	t4.join();
	std::cout << "Final value of n is " << n << "\n";
	std::cout << "end testThread" << std::endl;
}

void thread_task() {
	std::cout << "hello thread" << std::endl;
}

void testMutex()
{
		std::mutex m;
	std::thread t(thread_task);
	t.join();

	//运行结果
	std::vector<thread> threads;
	for (int i=0; i<5; i++)
	{
		auto threadIndex = i;
		threads.push_back(std::thread([&m,&threadIndex](){
			m.lock();
			std::cout << "Hello form lamba thread"  << threadIndex << " " <<std::this_thread::get_id() << std::endl;
			m.unlock();
		}));
	}

	for (auto& thread:threads) 
	{
		thread.join();
	}
}


std::mutex mtx;

void print_block(int n, char c)
{
	std::unique_lock<std::mutex> lck(mtx);
	for (int i =0; i < n; i++){
		std::cout << c;
	}
	std::cout << "\n";
}

void testUniqueLock()
{
	std::thread th1(print_block, 50, '*');
	std::thread th2(print_block, 50, '&');

	th1.join();
	th2.join();
}



std::condition_variable cv;

int cargo = 0;

bool shipment_available()
{
	return cargo != 0;
}

void consume(int n)
{
	for (int i=0; i < 10; ++i){
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, shipment_available);
		std::cout << cargo << "\n";
		cargo = 0;
	}
}
void testCondition()
{
	std::thread consumer_thread(consume, 10);
	for (int i=0; i<10; i++)
	{
		while(shipment_available())
			std::this_thread::yield();
		std::unique_lock<std::mutex> lck(mtx);
		cargo = i + 1;
		cv.notify_one();
	}

	consumer_thread.join();
}

 int main(int argc, char const *argv[])
{


	std::cout << "Main Thread" << "\t" << std::this_thread::get_id() << std::endl;

	// testMutex();
	// testCount();
	// testThread();

	// testUniqueLock();
	testCondition();
	return 0;
}