#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <climits>
#include <cmath>

#define MAXSIZE 10000
#define Pi 3.141592657

typedef struct station
{
    long long enodedId;
    double longitude, latitude;
    int index;
} Station;

using namespace std;

const double R = 6378137.0; //����뾶����mΪ��λ

Station stations[MAXSIZE];
int dp[MAXSIZE][MAXSIZE];
int opr[MAXSIZE][MAXSIZE];
double weight[MAXSIZE][MAXSIZE];

double distance(const Station &u, const Station &v)
{
    double radLat1 = u.latitude * Pi / 180.0;
    double radLat2 = v.latitude * Pi / 180.0;
    double radLon1 = u.longitude * Pi / 180.0;
    double radLon2 = v.longitude * Pi / 180.0;

    return R * acos(cos(radLat1) * cos(radLat2) * cos(radLon1 - radLon2)
        + sin(radLat1) * sin(radLat2));
}

double Weight(int i, int k, int j)
{
    return weight[i][k] + weight[i][j] + weight[k][j];
}

string LCS(const string &X, const string &Y)
{
    memset(dp, 0, sizeof(dp));
    memset(opr, 0, sizeof(opr)); //1��ʾ��(i-1,j-1)->(i,j);2��ʾ(i,j-1)->(i,j);3��ʾ��(i-1,j)->(i,j)

    dp[0][0] = 0;
    for (int i = 1; i <= X.length(); ++i)
    {
        for (int j = 1; j <= Y.length(); ++j)
        {
            //cout << i << j << endl;
            if (X[i-1] == Y[j-1])
            {
               // cout << X[i-1] << Y[j-1] << endl;;
                dp[i][j] = dp[i-1][j-1] + 1;
                opr[i][j] = 1;
            }
            else
            {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                if (dp[i][j] == dp[i][j-1])
                    opr[i][j] = 2;
                else
                    opr[i][j] = 3;
            }
        }
    }

    string sub;
    int i = X.length();
    int j = Y.length();
    while (i != 0 && j != 0)
    {
        if (opr[i][j] == 1)
        {
            sub = X[i-1] + sub;
            i--;
            j--;
        }
        else if (opr[i][j] == 2)
            j--;
        else
            i--;
    }

    return sub;
}

int MaxSum(const vector<int> &a, int &left, int &right)
{
    int sum = 0;
    int max = -INT_MAX;
    int l, r;

    for (int i = 0; i < a.size(); ++i)
    {
        if (sum + a[i] < 0)
        {
            sum = 0;
            l = i + 1;
        }
        else
        {
            sum += a[i];
            r = i;
        }
        if (sum > max)
        {
            max = sum;
            left = l;
            right = r;
        }
    }

    return max;
}

double MinWeightTriangulation(const int &n)
{
    memset(dp, 0, sizeof(dp));
    memset(opr, 0, sizeof(opr));

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            weight[j][i] = weight[i][j] = distance(stations[i], stations[j]);

    for (int r = 2; r <= n; r++)
        for (int i = 1; i <= n-r+1; i++)
        {
            int j = i + r - 1;
            dp[i][j] = dp[i + 1][j] + Weight(i - 1, i, j);
            opr[i][j] = i;
            for (int k = i+1; k < j; k++)
            {
                int u = dp[i][k] + dp[k + 1][j] + Weight(i - 1, k, j);
                if (u < dp[i][j])
                {
                    dp[i][j] = u;
                    opr[i][j] = k;
                }
            }
        }

    double len = 0;
    for (int i = 0; i < n-1; i++)
    {
        len += weight[i][i+1];
    }
    len += weight[n-1][0];

    return (len + dp[1][n-1]) / 2;
}

void TraceBack(int i, int j)
{
    if (i == j)
        return;

    TraceBack(i, opr[i][j]);
    TraceBack(opr[i][j] + 1, j);

    cout << "�����ʷֶ��㣺V" << i-1 << ",V" << j << ",V" << opr[i][j] << endl;
}
vector<bool> Knapspack(const int &c, const vector<int> &weight, const vector<int> &value, int &maxn)
{
    int n = weight.size();
    vector<bool> result(n, false);
    memset(dp, 0, sizeof(dp));
    memset(opr, 0, sizeof(opr)); //1��ʾ��(i+1,j)->(i,j);2��ʾ(i+1,j)->(i,j-weight[i]);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= c; j++)
        {
            if (j < weight[i]) {
                dp[i + 1][j] = dp[i][j];
                opr[i + 1][j] = 1;
            } else {
                dp[i + 1][j] = max(dp[i][j], dp[i][j - weight[i]] + value[i]);
                if (dp[i + 1][j] == dp[i][j - weight[i]] + value[i])
                    opr[i + 1][j] = 2;
                else
                    opr[i + 1][j] = 1;
            }
        }
    }

    int i = n, j = c;
    while(i != 0)
    {
        if(opr[i][j] == 2)
        {
            result[i - 1] = true;
            j = j - weight[i - 1];
        }
        i--;
    }

    maxn = dp[n][c];
    return result;
}

int main(int argc, char const *argv[])
{
    int choose = 0;
    while (choose != 5)
    {
        cout << "��ѡ�����²�����" << endl;
        cout << "1 �����������" << endl;
        cout << "2 ����Ӷκ�" << endl;
        cout << "3 ͹����������ʷ�" << endl;
        cout << "4 0-1����" << endl;
        cout << "5 �˳�" << endl;

        while (cin >> choose, !(choose >= 1 && choose <= 5))
        {
            cout << "���벻�Ϸ�������������" << endl;
            cin.clear();
            cin.sync();
        }
        cout << "-----------------------------------------------------------------" << endl;

        switch (choose)
        {
            case 1:
            {
                ifstream in("����1.�������������������.txt", ios_base::in);
                if (!in.is_open())
                {
                    cout << "Error opening file..." << endl;
                    exit(1);
                }

                //����A��B��C��D�ĸ���
                string A, B, C, D;
                int conditon = 0;
                char ch;
                while (in >> ch)
                {
                    if(ch >= 'A' && ch <= 'D' && in.get() == ':')
                        conditon = ch;
                    else if(ch != ' ' && ch != '\n' && ch != ':')
                        switch (conditon)
                        {
                            case 'A':
                                A += ch;
                                break;
                            case 'B':
                                B += ch;
                                break;
                            case 'C':
                                C += ch;
                                break;
                            case 'D':
                                D += ch;
                                break;
                        }
                }

                cout << "A-B��������Ӵ���" << LCS(A, B) << endl;
                cout << "C-D��������Ӵ���" << LCS(C, D) << endl;
                cout << "A-D��������Ӵ���" << LCS(A, D) << endl;
                cout << "C-B��������Ӵ���" << LCS(C, B) << endl;

                in.close();
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            case 2:
            {
                ifstream in1("����2.����Ӷκ���������-����1.txt", ios_base::in);
                ifstream in2("����2.����Ӷκ���������-����2.txt", ios_base::in);
                if (!in1.is_open() || !in2.is_open())
                {
                    cout << "Error opening file..." << endl;
                    exit(1);
                }

                vector<int> a;
                int num;
                int left, right;

                while(in1 >> num)
                    a.push_back(num);
                int len = MaxSum(a, left, right);

                cout << "����1������Ӷ�:" << endl;

                int sum = 0;
                for (int i = left; i <= right; ++i)
                {
                    cout << a[i] << ' ';
                    sum += a[i];
                }
                cout << endl << "����ֶ�Ϊ��" << left << "��" << right << " ��Ϊ��" << sum << endl;

                a.clear();
                while(in2 >> num)
                    a.push_back(num);
                len = MaxSum(a, left, right);

                cout << endl << "����2������Ӷ�:" << endl;
                for (int i = left; i <= right; ++i)
                {
                    cout << a[i] << ' ';
                }
                cout << endl << "����ֶ�Ϊ��" << left << "��" << right << " ��Ϊ��" << len << endl;

                in1.close();
                in2.close();
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            case 3:
            {
                ifstream in1("����3-1.21����վ͹���������.txt", ios_base::in);
                ifstream in2("����3-2.29����վ͹���������.txt", ios_base::in);

                if (!in1.is_open() || !in2.is_open())
                {
                    cout << "Error opening file..." << endl;
                    exit(1);
                }
                int n = 0;
                while (in1 >> stations[n].enodedId >> stations[n].longitude
                    >> stations[n].latitude >> stations[n].index)
                    n++;
                cout << "21����վ͹����ε����������ʷ�ֵΪ�� " << MinWeightTriangulation(n) << endl;
                cout << "���������ʷֽṹΪ��" << endl;
                TraceBack(1, n - 1);

                n = 0;
                while (in2 >> stations[n].enodedId >> stations[n].longitude
                    >> stations[n].latitude >> stations[n].index)
                    n++;
                cout << endl << "29����վ͹����ε����������ʷ�ֵΪ�� " << MinWeightTriangulation(n) << endl;
                cout << "���������ʷֽṹΪ��" << endl;
                TraceBack(1, n - 1);

                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            case 4:
			{
                ifstream in("����4.����������������.txt", ios_base::in);
                if (!in.is_open())
                {
                    cout << "Error opening file..." << endl;
                    exit(1);
                }

                int c;
                int num;
                int maxn = 0;
                string line;
                vector<int> weight;
                vector<int> value;

                in >> c;
                in.get(); //��ȡ����Ļ��з�
                getline(in, line);
                istringstream iss(line);
                while (iss >> num)
                    weight.push_back(num);
				getline(in, line);
				iss.clear(); //����iss״̬
                iss.str(line);
                while (iss >> num)
                    value.push_back(num);

                vector<bool> result = Knapspack(c, weight, value, maxn);

                cout <<  "��һ�����ݵ���󱳰�װ�ؼ�ֵ�� " << maxn << endl;
                cout << "װ�ص���Ʒ���£�(��ţ���������ֵ)" << endl;
                for (int i = 0; i < result.size(); ++i)
                {
                    if (result[i] == true)
                        cout << "(" << i+1 << "," << weight[i] << "," << value[i] << ") ";
                }
                cout << endl;

				weight.clear();
				value.clear();
				in >> c;
                in.get(); //��ȡ����Ļ��з�
                getline(in, line);
                iss.clear();
                iss.str(line);
                while (iss >> num)
                    weight.push_back(num);
				getline(in, line);
				iss.clear(); //����iss״̬
                iss.str(line);
                while (iss >> num)
                    value.push_back(num);

                result = Knapspack(c, weight, value, maxn);

                cout << endl << "�ڶ������ݵ���󱳰�װ�ؼ�ֵ�� " << maxn << endl;
                cout << "װ�ص���Ʒ���£�(��ţ���������ֵ)" << endl;
                for (int i = 0; i < result.size(); ++i)
                {
                    if (result[i] == true)
                        cout << "(" << i+1 << "," << weight[i] << "," << value[i] << ") ";
                }
                cout << endl;
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }

            default:
                break;
        }
    }
    return 0;
}
