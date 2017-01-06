

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
#include <windows.h>

void ReaderPriority(std::string filename)
{
	std::fstream in(filename);
	std::vector<std::thread> threads;

	int id;			// 线程编号
	char role;		// 线程角色
	double delay;	// 开始时间
	double need;	// 延迟时间

	auto countLck = CreateSemaphore(NULL, 1, 1, NULL);
	auto writeLck = CreateSemaphore(NULL, 1, 1, NULL);

	int readCount = 0;
	while (in >> id >> role >> delay >> need)
	{
		if (role == 'R')
			threads.emplace_back(std::thread([&, id, delay, need]() {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 1000)));

			// 等待互斥信号，保证对readCount的访问、修改和互斥
			WaitForSingleObject(countLck, INFINITE);
			readCount++;
			// 读写互斥
			// 只要读者锁没有上锁就锁上
			if (readCount == 1)
				WaitForSingleObject(writeLck, INFINITE);
			ReleaseSemaphore(countLck, 1, NULL);

			std::cout << "reader thread " << id << " begin to read" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(need * 1000)));
			std::cout << "reader thread " << id << " finish reading" << std::endl;

			// 等待互斥信号，保证对readcount的访问、修改和互斥 
			WaitForSingleObject(countLck, INFINITE);
			readCount--;
			// 如果读者全部读完，唤醒写者
			if (readCount == 0)
				ReleaseSemaphore(writeLck, 1, NULL);
			ReleaseSemaphore(countLck, 1, NULL);
		}));
		else
			threads.emplace_back(std::thread([&, id, delay, need]() {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 1000)));

			// 读写互斥和写写互斥
			WaitForSingleObject(writeLck, INFINITE);

			std::cout << "writer thread " << id << " begin to write" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(need * 1000)));
			std::cout << "writer thread " << id << " finish writing" << std::endl;

			ReleaseSemaphore(writeLck, 1, NULL);
		}));

	}

	for (auto& thread : threads)
		thread.join();


	getchar();
}

void WriterPriority(std::string filename)
{
	std::fstream in(filename);
	std::vector<std::thread> threads;

	int id;			// 线程编号
	char role;		// 线程角色
	double delay;	// 开始时间
	double need;	// 延迟时间

	auto readCountLck = CreateSemaphore(NULL, 1, 1, NULL);
	auto writeCountLck = CreateSemaphore(NULL, 1, 1, NULL);
	auto writeLck = CreateSemaphore(NULL, 1, 1, NULL);
	auto readLck = CreateSemaphore(NULL, 1, 1, NULL);

	int readCount = 0;
	int writeCount = 0;
	while (in >> id >> role >> delay >> need)
	{
		if (role == 'R')
			threads.emplace_back(std::thread([&, id, delay, need]() {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 1000)));
			
			// 等待写者全部写完
			WaitForSingleObject(readLck, INFINITE);
			
			// 等待互斥信号，保证对readCount的访问、修改和互斥
			WaitForSingleObject(readCountLck, INFINITE);
			readCount++;
			// 读写互斥
			// 只要写者锁没有上锁就锁上
			if (readCount == 1)
				WaitForSingleObject(writeLck, INFINITE);
			ReleaseSemaphore(readCountLck, 1, NULL);

			ReleaseSemaphore(readLck, 1, NULL);

			std::cout << "reader thread " << id << " begin to read" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(need * 1000)));
			std::cout << "reader thread " << id << " finish reading" << std::endl;

			// 等待互斥信号，保证对readcount的访问、修改和互斥 
			WaitForSingleObject(readCountLck, INFINITE);
			readCount--;
			// 如果读者全部读完，唤醒写者
			if (readCount == 0)
				ReleaseSemaphore(writeLck, 1, NULL);
			ReleaseSemaphore(readCountLck, 1, NULL);
		}));
		else
			threads.emplace_back(std::thread([&, id, delay, need]() {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 1000)));

			
			// 等待互斥信号，保证对writecount的访问、修改和互斥 
			WaitForSingleObject(writeCountLck, INFINITE);
			writeCount++;
			if (writeCount == 1)
				WaitForSingleObject(readLck, INFINITE);
			ReleaseSemaphore(writeCountLck, 1, NULL);

			// 读写互斥和写写互斥
			WaitForSingleObject(writeLck, INFINITE);
			std::cout << "writer thread " << id << " begin to write" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(need * 1000)));
			std::cout << "writer thread " << id << " finish writing" << std::endl;
			ReleaseSemaphore(writeLck, 1, NULL);

			// 等待互斥信号，保证对writecount的访问、修改和互斥 
			WaitForSingleObject(writeCountLck, INFINITE);
			writeCount--;
			// 如果写者全部读完，唤醒写者
			if (writeCount == 0)
				ReleaseSemaphore(readLck, 1, NULL);
			ReleaseSemaphore(writeCountLck, 1, NULL);
		}));
	}

	for (auto& thread : threads)
		thread.join();

	getchar();
}

int main()
{
	char ch;

	while (true)
	{
		//打印提示信息
		std::cout << "****************************************************" << std::endl;
		std::cout << "        1:Reader Priority" << std::endl;
		std::cout << "        2:Writer Priority" << std::endl;
		std::cout << "        3:Exit to Windows" << std::endl;
		std::cout << "****************************************************" << std::endl;
		std::cout << "Enter your choice(1, 2 or 3) : ";
		//如果信息不正确，继续输入
		while (true) {
			ch = getchar();
			if (ch == '1' || ch != '2' || ch != '3')
				break;
			std::cout << "Wrong choice, please input again." << std::endl;
		}
		system("cls");
		//选择3，返回
		if (ch == '3')
			return 0;
		//选择1，读者优先
		else if (ch == '1')
			ReaderPriority("thread.dat");
		//选择2，写者优先
		else
			WriterPriority("thread.dat");
		//结束
		std::cout << "\nPress Any Key To Continue : ";
		getchar();
		system("cls");
	}
	return 0;
}

