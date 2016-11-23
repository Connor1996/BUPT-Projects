// N-�ʺ�����Ŀ��پֲ������㷨
// �ο���Rok Sosic and Jun Gu. A Polynomial Time Algorithm for the N-Queens Problem. SIGART Bulletin, 1(3):7-11, 1990.

#include "stdafx.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "math.h"

long *pSolution;    // ��
long N;	            // �ʺ����
int sqrt_N;         // ���ڲ�����Χ��0 ~ N-1�������
long NumCollisions; // ��ǰ��ĳ�ͻ����

// ���Խ���, ͬһ���Խ����� i - pSolution[i] Ϊ�������±귶Χ -(N-1) ~ (N-1),ӳ�䵽 0 ~ (2N-2) [ͨ�� + (N-1)]
long *pPosDiagonal;

// ���Խ���, ͬһ���Խ����� i + pSolution[i] Ϊ�������±귶Χ 0 ~ (2N-2)
long *pNegDiagonal;

/*----------------------------------------------
����������������Ԫ
 ----------------------------------------------*/
inline void Swap(long &x, long &y)
{
	long temp;

	temp = y;
	y = x;
	x = temp;
}

/*----------------------------------------------
��������������һ��������У���Ϊ��ʼ��
 ----------------------------------------------*/
void GeneratePermutation()
{
	for (long i = 0; i < N; i++) pSolution[i] = i;

	int high, low;
	long rand_index;

	for (long i = 0; i < N; i++)
	{
		// ���ǵ�N����ֵ���ܴܺ������������ƴ�Ӷ���
		high = rand() % sqrt_N;
		low = rand()% sqrt_N;
		rand_index = high * sqrt_N + low;

		Swap(pSolution[i],pSolution[rand_index]);
	}
}

/*----------------------------------------------
�����������ͻ�ĸ���
 ----------------------------------------------*/
long CountCollisions()
{
	long max = 2 * N - 1;

	NumCollisions = 0;

	for (long i = 0; i < max; i++)
	{
		NumCollisions += pPosDiagonal[i] > 1 ? pPosDiagonal[i] - 1: 0;
		NumCollisions += pNegDiagonal[i] > 1 ? pNegDiagonal[i] - 1: 0;
	}

	return NumCollisions;
}

/*----------------------------------------------
���������ݽ⣬���������Խ��߶�Ӧ�Ļʺ���������
 ----------------------------------------------*/
void SetDiagonals()
{
	// ���ȸ������Խ��ߵ����鸳��ʼֵ 0
	memset(pPosDiagonal,0,sizeof(long)*(2*N-1));
	memset(pNegDiagonal,0,sizeof(long)*(2*N-1));

	for (long i = 0; i < N; i++)
	{
		pPosDiagonal[i - pSolution[i] + N -1]++;
		pNegDiagonal[i + pSolution[i]]++;
	}
}

/*----------------------------------------------
���������һ�£�������� pSolution[i], pSolution[j], ��ͻ�Ƿ����٣�
 ----------------------------------------------*/
long SwapEvaluate(long i, long j)
{
	long ret = 0;

	// ��������ͬһ�������Խ�����
	if (i - pSolution[i] == j - pSolution[j])
	{
		ret = (pPosDiagonal[i - pSolution[i] + N -1] > 2 ? 2: 1) + (pNegDiagonal[i + pSolution[i]] > 1 ? 1 : 0) +
			   (pNegDiagonal[j + pSolution[j]] > 1 ? 1 : 0) -
			   (pNegDiagonal[i + pSolution[j]] > 0 ? 2 : 1) -
			   (pPosDiagonal[i - pSolution[j] + N -1] > 0 ? 1: 0) - (pPosDiagonal[j - pSolution[i] + N -1] > 0 ? 1: 0);

		return ret;
	}

	// ��������ͬһ�����Խ�����
	if (i + pSolution[i] == j + pSolution[j])
	{
		ret = (pNegDiagonal[i + pSolution[i]] > 2 ? 2: 1) + (pPosDiagonal[i - pSolution[i] + N -1] > 1 ? 1 : 0) +
			  (pPosDiagonal[j - pSolution[j] + N -1] > 1 ? 1 : 0) -
			  (pPosDiagonal[i - pSolution[j] + N -1] > 0 ? 2 : 1) -
			  (pNegDiagonal[i + pSolution[j]] > 0 ? 1: 0) - (pNegDiagonal[j + pSolution[i]] > 0 ? 1: 0);

		return ret;
	}


	// һ����������������ڲ�ͬ�ĶԽ�����
	ret = (pPosDiagonal[i - pSolution[i] + N -1] > 1 ? 1 : 0) + (pNegDiagonal[i + pSolution[i]] > 1 ? 1 : 0) +
		  (pPosDiagonal[j - pSolution[j] + N -1] > 1 ? 1 : 0) + (pNegDiagonal[j + pSolution[j]] > 1 ? 1 : 0) -
		  (pPosDiagonal[i - pSolution[j] + N -1] > 0 ? 1 : 0) - (pNegDiagonal[i + pSolution[j]] > 0 ? 1 : 0) -
		  (pPosDiagonal[j - pSolution[i] + N -1] > 0 ? 1 : 0) - (pNegDiagonal[j + pSolution[i]] > 0 ? 1 : 0);

	return ret; // ret > 0 ������ͻ���٣�ret < 0 ��ʾ��ͻ����
}

/*----------------------------------------------
���������� pSolution[i], pSolution[j], ���¶Խ������鼰��ͻ����
 ----------------------------------------------*/
void SwapQueens(long i, long j, long gain)
{
	pPosDiagonal[i - pSolution[i] + N -1] --;
	pNegDiagonal[i + pSolution[i]] --;
	pPosDiagonal[j - pSolution[j] + N -1] --;
	pNegDiagonal[j + pSolution[j]] --;

	Swap(pSolution[i], pSolution[j]);

	pPosDiagonal[i - pSolution[i] + N -1] ++;
	pNegDiagonal[i + pSolution[i]] ++;
	pPosDiagonal[j - pSolution[j] + N -1] ++;
	pNegDiagonal[j + pSolution[j]] ++;

	NumCollisions -= gain;
}

/*----------------------------------------------
������
 ----------------------------------------------*/
int main(int argc, char* argv[])
{
	clock_t start, finish;
	start = clock();

	sscanf(argv[1],"%ld",&N);

	sqrt_N = (int) sqrt(N);

	// �����Ŀռ�
	pSolution = new long[N]; // ʹ���±� 0 - (N-1)

	// �������Խ����ϵ�����ռ䣬������ʼֵΪ0
	pPosDiagonal = new long[2*N-1];

	// ���为�Խ����ϵ�����ռ䣬������ʼֵΪ0
	pNegDiagonal = new long[2*N-1];

	// ��������
	long long m = 0;

	do {
		// ����һ�������
		GeneratePermutation();

		//����������һ
		m++;

		// �������Խ��߶�Ӧ�Ļʺ������鸳ֵ
		SetDiagonals();

		CountCollisions();

		bool flag = true;
		long gain;

		while (flag)
		{
			flag = false;
			for (long i = 0; i < N; i++)
				for (long j = i; j < N; j++)
					// ��pSolution[i] �� pSolution[j]��Ӧ�ĶԽ����г�ͻ
					if (pPosDiagonal[i - pSolution[i] + N -1] > 1 || pNegDiagonal[i + pSolution[i]] > 1 ||
						pPosDiagonal[j - pSolution[j] + N -1] > 1 || pNegDiagonal[j + pSolution[j]] > 1)
					{
						// �ж�һ�£��������pSolution[i]��pSolution[j]���Ƿ���Խ��ͳ�ͻ����
						gain = SwapEvaluate(i, j);

						// �������������ͻ�ļ��٣���ֵ�ý���
						if ( gain > 0)
 						{
							flag = true; // ��ǣ�֤�����ֵ������˽���

							SwapQueens(i, j, gain); // ���� 2���ʺ󣬲����³�ͻ����
						}
					}
		}

	} while (NumCollisions > 0);

	finish = clock();

	double duration = (double) (finish-start)/CLOCKS_PER_SEC;

	printf("random solution: %lld\n", m);
	printf("time:%f seconds\n", duration);

	return 0;
}