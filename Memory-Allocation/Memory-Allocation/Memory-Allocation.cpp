// Memory-Allocation.cpp : �������̨Ӧ�ó������ڵ㡣
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
			SYSTEM_INFO info;  //ϵͳ��Ϣ
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

			//�ڴ�״��
			MEMORYSTATUS status; //�ڴ�״̬
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

			//����һ����ʾ�ڴ������Ϣ��ÿ�β������ڴ������Ϣ����
			//��Ҫ�鿴�ڴ������Ϣ������ȡ��ע��

			MEMORY_BASIC_INFORMATION mem;//�ڴ������Ϣ
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
			// �ȴ�allocatorһ���ڴ��������
			WaitForSingleObject(semaphoreTrack, INFINITE);
			outputInfo();
			// �ͷ��ź���֪ͨallocator����ִ����һ���ڴ����
			ReleaseSemaphore(semaphoreAlloc, 1, NULL);
		}

		outfile.close();
	});

	auto threadAlloc = std::thread([&]() {
		struct Operation
		{
			int time;//��ʼʱ��
			int block;//�ڴ�ҳ��
			int oper;//����
			int protection;//Ȩ��
		};

		struct Trace //����ÿһ�η��������ݽṹ
		{
			LPVOID start;//��ʼ��ַ
			long size;   //����Ĵ�С
		};

		std::ifstream in("opfile", std::ifstream::binary);

		Operation op;
		SYSTEM_INFO info;
		GetSystemInfo(&info);
		Trace traceArray[5];
		// ��Ӧ��Ȩ��
		const std::vector<DWORD> protection = {
			PAGE_READONLY,
			PAGE_READWRITE,
			PAGE_EXECUTE,
			PAGE_EXECUTE_READ,
			PAGE_EXECUTE_READWRITE,
			PAGE_READONLY
		};

		size_t index = 0;
		// ��Ӧ�Ĳ���
		const std::vector<std::function<void(void)>> action = {
			// ����һ������
			[&]()
			{
				cout << "reserve now" << endl;

				traceArray[index].start = VirtualAlloc(NULL, op.block * info.dwPageSize,
					MEM_RESERVE, PAGE_NOACCESS);
				traceArray[index].size = op.block * info.dwPageSize;
				cout << "starting address:"
					<< traceArray[index].start << '\t' << "size:" << traceArray[index].size << endl;
			},

			// �ύһ������
			[&]()
			{
				cout << "commit now" << endl;

				traceArray[index].start = VirtualAlloc(traceArray[index].start,
					traceArray[index].size, MEM_COMMIT, protection[op.protection]);
				cout << "starting address:"
					<< traceArray[index].start << '\t' << "size:" << traceArray[index].size << endl;
			},

			// ��һ������
			[&]()
			{
				cout << "lock now" << endl;
				cout << "starting address:" << traceArray[index].start << '\t' <<
					"size:" << traceArray[index].size << endl;
				if (!VirtualLock(traceArray[index].start, traceArray[index].size))
					cout << GetLastError() << endl;
				//GetLastError()�������ش����
			},

			// ����һ������
			[&]()
			{
				cout << "unlock now" << endl;
				cout << "starting address:" << traceArray[index].start << 
					'\t' << "size:" << traceArray[index].size << endl;
				if (!VirtualUnlock(traceArray[index].start, traceArray[index].size))
					cout << GetLastError() << endl;

			},

			// ����һ������
			[&]()
			{
				cout << "decommit now" << endl;
				cout << "starting address:" << traceArray[index].start << '\t' <<
					"size:" << traceArray[index].size << endl;
				if (!VirtualFree(traceArray[index].start, traceArray[index].size, MEM_DECOMMIT))
					cout << GetLastError() << endl;

			},

			// �ͷ�һ������
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
				//�ȴ�tracker��ӡ�������ź���
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
				//0-������1-�ύ��2-����3-������4-���գ�5-�ͷ�
				action[op.oper]();
				index++;

				//�ͷ��ź���֪ͨtracker���Դ�ӡ��Ϣ
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



