#include <iostream>
#include <fstream>
#include <algorithm>
#include <utility>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cmath>

#define MAXSIZE 3000
#define Pi 3.141592657

using namespace std;

typedef struct station
{
    long long enodedId;
    double longitude, latitude;
    double k_dist;
} Station;

Station stations[MAXSIZE]; //�����վ���ݵ�����
const double R = 6378137.0; //����뾶����mΪ��λ
int n = 0;

//�鲢����ĺϲ�����
void Merge(Station a[], int l, int m, int r)
{
    int i = l, j = m + 1, k = l;
    Station temp[MAXSIZE];

    //��k_dist��С����˳�����Ҳ��ֺϲ���temp����
    while (i <= m && j <= r)
        if (a[i].k_dist < a[j].k_dist)
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];

    //����һ�����Ⱥϲ��꣬������һ����ʣ��Ԫ��ֱ�Ӻϲ���temp����
    if (i > m)
        for (int q = j; q <= r; q++)
            temp[k++] = a[q];
    else
        for (int q = i; q <= m; q++)
            temp[k++] = a[q];

    //��temp���鸴�Ƹ�a����
    for (int q = l; q <= r; q++)
        a[q] = temp[q];
}

//�鲢����
void MergeSort(Station a[], int left, int right)
{
    if (left < right)
    {
        int i = (left + right) >> 1;

        //�ֱ�����Ҳ��ֽ��й鲢����
        MergeSort(a, left, i);
        MergeSort(a, i + 1, right);

        //�ϲ�������
        Merge(a, left, i, right);
    }
}

//���ݸ���ֵ���������ΪС�ںʹ���������
int Partition(Station a[], int left, int right, Station x)
{
    int i = left, j = right;
    Station key = x;

    int loc = left;
    //������a�и�����Χ���ҵ�x���ڵ�λ�ã����������Ԫ�ؽ���
    while (a[loc].enodedId != x.enodedId)
        loc++;
    swap(a[left], a[loc]);

    //��С�ڸ���ֵ�ķ�����ߣ����ڸ���ֵ�ķ����ұ�
    while (i < j)
    {
        while (a[j].k_dist > key.k_dist && i < j)
            j--;
        if (i < j)
            a[i++] = a[j];

        while (a[i].k_dist < key.k_dist && i < j)
            i++;
        if (i < j)
            a[j--] = a[i];
    }
    a[i] = key;
    return i;
}

//��������
void QuickSort(Station a[], int left, int right)
{
    if (left >= right)
        return;

    int i = Partition(a, left, right, a[left]);
    QuickSort(a, left, i - 1);
    QuickSort(a, i + 1, right);
}

//����ʱ��ѡ��
Station Select(Station a[], int left, int right, int k)
{
    //��ģС��75��ֱ�ӽ�������
    if (right - left < 75)
    {
        QuickSort(a, left, right);
        return a[left + k - 1];
    }

    //5��Ϊһ�飬�������򣬲�����ֵ��ѡ����
    for  (int i = 0; i <= (right - left - 4)/5; ++i)
    {
        QuickSort(a, left + 5*i, left + 5*i + 4);
        swap(a[left + 5*i + 2], a[left + i]);
    }

    //����ѡ����ֵ��Ѱ����ֵ����ֵ
    Station x = Select(a, left, left + (right - left - 4)/5, (right - left - 4)/10);

    //������ֵ����ֵ��������������
    //�ж�k���󲿷ֻ����Ҳ��֣������еݹ�
    int i = Partition(a, left, right, x),
        j = i - left + 1;
    if (k <= j)
        return Select(a, left, i, k);
    else
        return Select(a, i+1, right, k-j);

}


//��������վ��ľ���
double distance(const Station &u, const Station &v)
{
    double radLat1 = u.latitude * Pi / 180.0;
    double radLat2 = v.latitude * Pi / 180.0;
    double radLon1 = u.longitude * Pi / 180.0;
    double radLon2 = v.longitude * Pi / 180.0;

    return R * acos(cos(radLat1) * cos(radLat2) * cos(radLon1 - radLon2)
        + sin(radLat1) * sin(radLat2));
}

//Ѱ�������Ժʹν����
//a1��b1Ϊ�����ԣ�a2��b2Ϊ�ν����
pair<double, double> Closeset(Station x[], int left, int right,
                                int &a1, int &b1, int &a2, int &b2)
{
    if (right - left == 1) //2���������
    {
        a1 = left;
        b1 = right;
        a2 = -1;
        b2 = -1;
        return make_pair(distance(x[a1], x[b1]), 0x7fffffff);
    }

    if (right - left == 2) //3���������
    {
        //�ֱ������ֿ��ܵ���С����
        double d1 = distance(x[left], x[left + 1]);
        double d2 = distance(x[left + 1], x[right]);
        double d3 = distance(x[left], x[right]);

        //�ҵ���С����ʹ�С���룬������a1��b1��a2��b2
        if (d1 <= d2 && d2 <= d3)
        {
            a1 = left;
            b1 = left + 1;
            a2 = left + 1;
            b2 = right;
            return make_pair(d1, d2);
        }
        if (d1 <= d3 && d3 <= d2)
        {
            a1 = left;
            b1 = left + 1;
            a2 = left;
            b2 = right;
            return make_pair(d1, d3);
        }
        if (d2 <= d1 && d1 <= d3)
        {
            a1 = left + 1;
            b1 = right;
            a2 = left;
            b2 = left + 1;
            return make_pair(d2, d1);
        }
        if (d2 <= d3 && d3 <= d1)
        {
            a1 = left + 1;
            b1 = right;
            a2 = left;
            b2 = right;
            return make_pair(d2, d3);
        }
        if (d3 <= d1 && d1 <= d2)
        {
            a1 = left;
            b1 = right;
            a2 = left;
            b2 = left + 1;
            return make_pair(d3, d1);
        }
        if (d3 <= d2 && d2 <= d1)
        {
            a1 = left;
            b1 = right;
            a2 = left + 1;
            b2 = right;
            return make_pair(d3, d2);
        }
    }

    //���е�Ϊ�ָ������Ҳ��ֵ���̾���ʹζ̾���
    int mid = (left + right) >> 1;
    int l_a1, l_b1, l_a2, l_b2;
    int r_a1, r_b1, r_a2, r_b2;
    pair<double, double> leftPair = Closeset(x, left, mid, l_a1, l_b1, l_a2, l_b2);
    pair<double, double> rightPair = Closeset(x, mid + 1, right, r_a1, r_b1, r_a2, r_b2);

    double d1, d2;
    //�Ƚ����Ҳ��ֵĽ��������d1��a1��b1
    if (leftPair.first <= rightPair.first)
    {
        d1 = leftPair.first;
        a1 = l_a1;
        b1 = l_b1;
    }
    else
    {
        d1 = rightPair.first;
        a1 = r_a1;
        b1 = r_b1;
    }
    //����d2��a2��b2
    if (max(leftPair.first, rightPair.first) <= min(leftPair.second, rightPair.second))
    {
        if (leftPair.first < rightPair.first)
        {
            d2 = rightPair.first;
            a2 = r_a1;
            b2 = r_b1;
        }
        else
        {
            d2 = leftPair.first;
            a2 = l_a1;
            b2 = l_b1;
        }
    }
    else if (leftPair.second <= rightPair.second)
    {
        d2 = leftPair.second;
        a2 = l_a2;
        b2 = l_b2;
    }
    else
    {
        d2 = rightPair.second;
        a2 = r_a2;
        b2 = r_b2;
    }

    //�ҳ����п�����ӽ���Ժ�ѡ�ߣ�������x�����������¼��t��
    int t[MAXSIZE];
    int k = 0;
    for (int i = left; i <= right; i++)
        if (fabs(x[mid].longitude - x[i].longitude) < d1)
            t[k++] = i;
    //����γ�ȶ�t��������
    sort(t, t + k, [x](int a, int b){return x[a].latitude < x[a].latitude; });
    //�������п�����ӽ���Ժ�ѡ��
    for (int i = 0; i < k; i++)
        for (int j = i + 1; j < k && x[t[j]].latitude - x[t[i]].latitude < d1; j++)
        {
            double dp = distance(x[t[i]], x[t[j]]);
            //������̾���ʹζ̾���
            if (dp <= d1)
            {
                d2 = d1;
                a2 = a1;
                b2 = b1;

                d1 = dp;
                a1 = t[i];
                b1 = t[j];
            }
            else if (dp < d2)
            {
                d2 = dp;
                a2 = t[i];
                b2 = t[j];
            }
        }

    return make_pair(d1, d2);
}

int main(int argc, char const *argv[])
{
    //���ݶ���
    ifstream in("data.txt", ios_base::in);
    if (!in.is_open())
    {
        cout << "Error opening file..." << endl;
        exit(1);
    }
    while (!in.eof())
    {
        in >> stations[n].enodedId >> stations[n].longitude >> stations[n].latitude >> stations[n].k_dist;
        n++;
    }
    n -= 2;

    int choose = 0;
    while (choose != 5)
    {
        cout << "��ѡ�����²�����" << endl;
        cout << "1 ���úϲ������㷨�����ݻ�վk-dist���룬�Ի�վ��С�����������" << endl;
        cout << "2 ���ÿ��������㷨�����ݻ�վk-dist���룬�Ի�վ��С�����������" << endl;
        cout << "3 ����ʱ��ѡ��" << endl;
        cout << "4 ƽ��������" << endl;
        cout << "5 �˳�" << endl;

        while (cin >> choose, !(choose >= 1 && choose <= 5))
        {
            cout << "���벻�Ϸ�������������" << endl;
            cin.clear();
            cin.sync();
        }
        cout << "-----------------------------------------------------------------" << endl;

        Station OrderStations[MAXSIZE];
        memcpy(OrderStations, stations, sizeof(stations));
        switch (choose)
        {
            case 1:
                MergeSort(OrderStations, 0, n);
                for (int i = 0; i <= n; ++i)
                {
                    cout << OrderStations[i].enodedId << '\t' << OrderStations[i].longitude << '\t' <<  OrderStations[i].latitude
                        << '\t' << OrderStations[i].k_dist << endl;
                }
                cout << "--------------------------������-----------------------------" << endl;
                break;
            case 2:
                QuickSort(OrderStations, 0, n);
                for (int i = 0; i <= n; ++i)
                {
                    cout << OrderStations[i].enodedId << '\t' << OrderStations[i].longitude << '\t' <<  OrderStations[i].latitude
                        << '\t' << OrderStations[i].k_dist << endl;
                }
                cout << "--------------------------������------------------- ----------" << endl;
                break;
            case 3:
                Station temp;
                temp = Select(OrderStations, 0, n, 1);
                cout << "k_distֵ��С�Ļ�վ�� " << '\t' << temp.enodedId << '\t' << temp.longitude << '\t' << temp.latitude << '\t' << temp.k_dist << endl;
                temp = Select(OrderStations, 0, n, 5);
                cout << "k_distֵ��5С�Ļ�վ: " << '\t' << temp.enodedId << '\t' << temp.longitude << '\t' << temp.latitude << '\t' << temp.k_dist << endl;
                temp = Select(OrderStations, 0, n, 50);
                cout << "k_distֵ��50С�Ļ�վ: " << '\t' << temp.enodedId << '\t' << temp.longitude << '\t' << temp.latitude << '\t' << temp.k_dist << endl;
                temp = Select(OrderStations, 0, n, n + 1);
                cout << "k_distֵ���Ļ�վ: " << '\t' << temp.enodedId << '\t' << temp.longitude << '\t' << temp.latitude << '\t' << temp.k_dist << endl;
                cout << "--------------------------������-----------------------------" << endl;
                break;
            case 4:
            {
                sort(OrderStations, OrderStations + n + 1, [](Station a, Station b){return a.longitude < b.longitude; });
                int a1, b1, a2, b2;
                pair<double, double> res = Closeset(OrderStations, 0, n, a1, b1, a2, b2);

                cout << "���������2����վ: " << OrderStations[a1].enodedId << " �� " << OrderStations[b1].enodedId <<
                    "\t����Ϊ: " << fixed << res.first << endl;
                cout << "����ν���2����վ: " << OrderStations[a2].enodedId << " �� " << OrderStations[b2].enodedId <<
                    "\t����Ϊ: " << fixed << res.second << endl;
                cout << "--------------------------������-----------------------------" << endl;
                break;
            }
            case 5:
                exit(0);
                break;
        }
    }

    return 0;
}
