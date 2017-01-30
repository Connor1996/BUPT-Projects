// Memory-Allocation.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include <fstream>
#include <thread>
#include <functional>
#include <vector>
#include <windows.h>


using std::cout;
using std::endl;
int main()
{
	auto semaphoreTrack = CreateSemaphore(NULL, 1, 1, NULL);
	auto semaphoreAlloc = CreateSemaphore(NULL, 1, 1, NULL);
	auto isEnd = false;

	auto threadTrack = std::thread([&]() {
		std::ofstream outfile("out.txt");
		
		auto outputInfo = [&]() {
			SYSTEM_INFO info;  //系统信息
			GetSystemInfo(&info);
			outfile << "dwActiveProcessorMask" << '\t' << info.dwActiveProcessorMask << endl;
			outfile << "dwAllocationGranularity" << '\t' << info.dwAllocationGranularity << endl;
			outfile << "dwNumberOfProcessors" << '\t' << info.dwNumberOfProcessors << endl;
			outfile << "dwOemId" << '\t' << info.dwOemId << endl;
			outfile << "dwPageSize" << '\t' << info.dwPageSize << endl;
			outfile << "dwProcessorType" << '\t' << info.dwProcessorType << endl;
			outfile << "lpMaximumApplicationAddress" << '\t' << info.lpMaximumApplicationAddress << endl;
			outfile << "lpMinimumApplicationAddress" << '\t' << info.lpMinimumApplicationAddress << endl;
			outfile << "wProcessorArchitecture" << '\t' << info.wProcessorArchitecture << endl;
			outfile << "wProcessorLevel" << '\t' << info.wProcessorLevel << endl;
			outfile << "wProcessorRevision" << '\t' << info.wProcessorRevision << endl;
			outfile << "wReserved" << '\t' << info.wReserved << endl;
			outfile << "************************************************************************************" << endl;

			//内存状况
			MEMORYSTATUS status; //内存状态
			GlobalMemoryStatus(&status);
			outfile << "dwAvailPageFile" << '\t' << status.dwAvailPageFile << endl;
			outfile << "dwAvailPhys" << '\t' << status.dwAvailPhys << endl;
			outfile << "dwAvailVirtual" << '\t' << status.dwAvailVirtual << endl;
			outfile << "dwLength" << '\t' << status.dwLength << endl;
			outfile << "dwMemoryLoad" << '\t' << status.dwMemoryLoad << endl;
			outfile << "dwTotalPageFile" << '\t' << status.dwTotalPageFile << endl;
			outfile << "dwTotalPhys" << '\t' << status.dwTotalPhys << endl;
			outfile << "dwTotalVirtual" << '\t' << status.dwTotalVirtual << endl;
			outfile << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;

			//以下一段显示内存基本信息，每次操作后内存基本信息不变
			//如要查看内存基本信息，可以取消注释

			MEMORY_BASIC_INFORMATION mem;//内存基本信息
			VirtualQuery(info.lpMinimumApplicationAddress, &mem,
				sizeof(MEMORY_BASIC_INFORMATION));
			outfile << "AllocationBase" << '\t' << mem.AllocationBase << endl;
			outfile << "AllocationProtect" << '\t' << mem.AllocationProtect << endl;
			outfile << "BaseAddress" << '\t' << mem.BaseAddress << endl;
			outfile << "Protect" << '\t' << mem.Protect << endl;
			outfile << "RegionSize" << '\t' << mem.RegionSize << endl;
			outfile << "State" << '\t' << mem.State << endl;
			outfile << "Type" << '\t' << mem.Type << endl;
			outfile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

		};
				
		while (!isEnd) {
			// 等待allocator一次内存分配活动结束
			WaitForSingleObject(semaphoreTrack, INFINITE);
			outputInfo();
			// 释放信号量通知allocator可以执行下一次内存分配活动
			ReleaseSemaphore(semaphoreAlloc, 1, NULL);
		}

		outfile.close();
	});

	auto threadAlloc = std::thread([&]() {
		struct Operation
		{
			int time;//起始时间
			int block;//内存页数
			int oper;//操作
			int protection;//权限
		};

		struct Trace //跟踪每一次分配活动的数据结构
		{
			LPVOID start;//起始地址
			long size;   //分配的大小
		};

		std::ifstream in("opfile", std::ifstream::binary);

		Operation op;
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		Trace traceArray[5];
		// 对应的权限
		const std::vector<DWORD> protection = {
			PAGE_READONLY,
			PAGE_READWRITE,
			PAGE_EXECUTE,
			PAGE_EXECUTE_READ,
			PAGE_EXECUTE_READWRITE,
			PAGE_READONLY
		};

		size_t index = 0;
		// 对应的操作
		const std::vector<std::function<void(void)>> action = {
			// 保留一个区域
			[&]()
			{
				cout << "reserve now" << endl;

				traceArray[index].start = VirtualAlloc(NULL, op.block * info.dwPageSize,
					MEM_RESERVE, PAGE_NOACCESS);
				traceArray[index].size = op.block * info.dwPageSize;
				cout << "starting address:"
					<< traceArray[index].start << '\t' << "size:" << traceArray[index].size << endl;
			},

			// 提交一个区域
			[&]()
			{
				cout << "commit now" << endl;

				traceArray[index].start = VirtualAlloc(traceArray[index].start,
					traceArray[index].size, MEM_COMMIT, protection[op.protection]);
				cout << "starting address:"
					<< traceArray[index].start << '\t' << "size:" << traceArray[index].size << endl;
			},

			// 锁一个区域
			[&]()
			{
				cout << "lock now" << endl;
				cout << "starting address:" << traceArray[index].start << '\t' <<
					"size:" << traceArray[index].size << endl;
				if (!VirtualLock(traceArray[index].start, traceArray[index].size))
					cout << GetLastError() << endl;
				//GetLastError()函数返回错误号
			},

			// 解锁一个区域
			[&]()
			{
				cout << "unlock now" << endl;
				cout << "starting address:" << traceArray[index].start << 
					'\t' << "size:" << traceArray[index].size << endl;
				if (!VirtualUnlock(traceArray[index].start, traceArray[index].size))
					cout << GetLastError() << endl;

			},

			// 回收一个区域
			[&]()
			{
				cout << "decommit now" << endl;
				cout << "starting address:" << traceArray[index].start << '\t' <<
					"size:" << traceArray[index].size << endl;
				if (!VirtualFree(traceArray[index].start, traceArray[index].size, MEM_DECOMMIT))
					cout << GetLastError() << endl;

			},

			// 释放一个区域
			[&]()
			{
				cout << "release now" << endl;
				cout << "starting address:" << traceArray[index].start << '\t' << 
					"size:" << traceArray[index].size << endl;
				if (!VirtualFree(traceArray[index].start, 0 ,MEM_RELEASE))
					cout << GetLastError() << endl;
			}
		};
			
		try
		{
			while (true)
			{
				//等待tracker打印结束的信号量
				WaitForSingleObject(semaphoreAlloc, INFINITE);

				in.read(reinterpret_cast<char *>(&op), sizeof(Operation));
				if (in.eof())
				{
					isEnd = true;
					break;
				}
				if (op.protection == 0)
					index = 0;
				std::this_thread::sleep_for(std::chrono::milliseconds(op.time));
				//0-保留；1-提交；2-锁；3-解锁；4-回收；5-释放
				action[op.oper]();
				index++;

				//释放信号量通知tracker可以打印信息
				ReleaseSemaphore(semaphoreTrack, 1, NULL);
			}
		} 
		catch (std::exception e)
		{
			cout << e.what() << endl;
		}

		in.close();
	});

	if (threadAlloc.joinable())
		threadAlloc.join();
	if (threadTrack.joinable())
		threadTrack.join();

	CloseHandle(semaphoreAlloc);
	CloseHandle(semaphoreTrack);

    return 0;
}



