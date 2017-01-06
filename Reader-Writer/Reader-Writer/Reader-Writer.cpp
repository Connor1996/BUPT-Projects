

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

	int id;			// �̱߳��
	char role;		// �߳̽�ɫ
	double delay;	// ��ʼʱ��
	double need;	// �ӳ�ʱ��

	auto countLck = CreateSemaphore(NULL, 1, 1, NULL);
	auto writeLck = CreateSemaphore(NULL, 1, 1, NULL);

	int readCount = 0;
	while (in >> id >> role >> delay >> need)
	{
		if (role == 'R')
			threads.emplace_back(std::thread([&, id, delay, need]() {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 1000)));

			// �ȴ������źţ���֤��readCount�ķ��ʡ��޸ĺͻ���
			WaitForSingleObject(countLck, INFINITE);
			readCount++;
			// ��д����
			// ֻҪ������û������������
			if (readCount == 1)
				WaitForSingleObject(writeLck, INFINITE);
			ReleaseSemaphore(countLck, 1, NULL);

			std::cout << "reader thread " << id << " begin to read" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(need * 1000)));
			std::cout << "reader thread " << id << " finish reading" << std::endl;

			// �ȴ������źţ���֤��readcount�ķ��ʡ��޸ĺͻ��� 
			WaitForSingleObject(countLck, INFINITE);
			readCount--;
			// �������ȫ�����꣬����д��
			if (readCount == 0)
				ReleaseSemaphore(writeLck, 1, NULL);
			ReleaseSemaphore(countLck, 1, NULL);
		}));
		else
			threads.emplace_back(std::thread([&, id, delay, need]() {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 1000)));

			// ��д�����дд����
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

	int id;			// �̱߳��
	char role;		// �߳̽�ɫ
	double delay;	// ��ʼʱ��
	double need;	// �ӳ�ʱ��

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
			
			// �ȴ�д��ȫ��д��
			WaitForSingleObject(readLck, INFINITE);
			
			// �ȴ������źţ���֤��readCount�ķ��ʡ��޸ĺͻ���
			WaitForSingleObject(readCountLck, INFINITE);
			readCount++;
			// ��д����
			// ֻҪд����û������������
			if (readCount == 1)
				WaitForSingleObject(writeLck, INFINITE);
			ReleaseSemaphore(readCountLck, 1, NULL);

			ReleaseSemaphore(readLck, 1, NULL);

			std::cout << "reader thread " << id << " begin to read" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(need * 1000)));
			std::cout << "reader thread " << id << " finish reading" << std::endl;

			// �ȴ������źţ���֤��readcount�ķ��ʡ��޸ĺͻ��� 
			WaitForSingleObject(readCountLck, INFINITE);
			readCount--;
			// �������ȫ�����꣬����д��
			if (readCount == 0)
				ReleaseSemaphore(writeLck, 1, NULL);
			ReleaseSemaphore(readCountLck, 1, NULL);
		}));
		else
			threads.emplace_back(std::thread([&, id, delay, need]() {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(delay * 1000)));

			
			// �ȴ������źţ���֤��writecount�ķ��ʡ��޸ĺͻ��� 
			WaitForSingleObject(writeCountLck, INFINITE);
			writeCount++;
			if (writeCount == 1)
				WaitForSingleObject(readLck, INFINITE);
			ReleaseSemaphore(writeCountLck, 1, NULL);

			// ��д�����дд����
			WaitForSingleObject(writeLck, INFINITE);
			std::cout << "writer thread " << id << " begin to write" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(need * 1000)));
			std::cout << "writer thread " << id << " finish writing" << std::endl;
			ReleaseSemaphore(writeLck, 1, NULL);

			// �ȴ������źţ���֤��writecount�ķ��ʡ��޸ĺͻ��� 
			WaitForSingleObject(writeCountLck, INFINITE);
			writeCount--;
			// ���д��ȫ�����꣬����д��
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
		//��ӡ��ʾ��Ϣ
		std::cout << "****************************************************" << std::endl;
		std::cout << "        1:Reader Priority" << std::endl;
		std::cout << "        2:Writer Priority" << std::endl;
		std::cout << "        3:Exit to Windows" << std::endl;
		std::cout << "****************************************************" << std::endl;
		std::cout << "Enter your choice(1, 2 or 3) : ";
		//�����Ϣ����ȷ����������
		while (true) {
			ch = getchar();
			if (ch == '1' || ch != '2' || ch != '3')
				break;
			std::cout << "Wrong choice, please input again." << std::endl;
		}
		system("cls");
		//ѡ��3������
		if (ch == '3')
			return 0;
		//ѡ��1����������
		else if (ch == '1')
			ReaderPriority("thread.dat");
		//ѡ��2��д������
		else
			WriterPriority("thread.dat");
		//����
		std::cout << "\nPress Any Key To Continue : ";
		getchar();
		system("cls");
	}
	return 0;
}

