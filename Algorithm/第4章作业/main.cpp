#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <climits>
#include <cmath>
#include <queue>
#include <map>
#include <algorithm>

#define MAXSIZE 10000
#define Pi 3.141592657

typedef struct station
{
    long long enodedId;
    double longitude, latitude;
    int index;
} Station;

typedef struct node
{
    struct node *left, *right;
    int weight;
    char ch;
} Node, *pNode;

typedef struct edge
{
    int u, v;
    double cost;
    bool operator < (const struct edge &m)const {
                return cost < m.cost;
        }
} Edge, *pEdge;

using namespace std;

const double R = 6378137.0; //����뾶����mΪ��λ

Station stations[MAXSIZE];
int dp[MAXSIZE][MAXSIZE];
int opr[MAXSIZE][MAXSIZE];
double weight[MAXSIZE][MAXSIZE];
int father[MAXSIZE];

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

struct cmp{
    bool operator()(pNode node1, pNode node2){
        return node1->weight > node2->weight;
    }
};

pNode HuffmanTree(int incidence[])
{
    priority_queue<pNode, vector<pNode>, cmp > heap;

    for (int i = 0; i <= 26; i++)
    {
        pNode haffman = new Node;
        haffman->left = NULL;
        haffman->right = NULL;
        haffman->weight = incidence[i];
        if (i == 0)
            haffman->ch = '#';
        else
            haffman->ch = i - 1 + 'a';
        heap.push(haffman);
    }

    while (heap.size() != 1)
    {
        pNode node1 = heap.top();
        heap.pop();
        pNode node2 = heap.top();
        heap.pop();

        pNode haffman = new Node;
        haffman->left = node1;
        haffman->right = node2;
        haffman->weight = node1->weight + node2->weight;
        heap.push(haffman);
    }

    return heap.top();
}

int printHuffman(pNode node, string str, int incidence[])
{
    if (node->left == NULL && node->right == NULL)
    {
        cout << node->ch << ": " << str << endl;
        int result = incidence[(node->ch == '#') ? 0 : (node->ch - 'a' + 1)] * str.length();
        delete node;

        return result;
    }

    int result1 = 0, result2 = 0;
    if (node->left)
        result1 = printHuffman(node->left, str + '0', incidence);
    if (node->right)
        result2 = printHuffman(node->right, str + '1', incidence);

	delete node;
    return result1 + result2;
}

void Dijkstra(double dist[], double map[][42], bool known[], int seq, int path[], int scale)
{
    dist[seq] = 0;
    known[seq] = true;

    while (1) {
        for (int i = 0; i < scale; i++)
            if (!known[i] && map[seq][i] > 0 && dist[seq] + map[seq][i] < dist[i]) {
                dist[i] = dist[seq] + map[seq][i];
                path[i] = seq;
            }
        seq = -1;
        double min = INT_MAX;
        for (int i = 0; i < scale; i++)
            if (!known[i] && min > dist[i])
            {
                min = dist[i];
                seq = i;
            }

        if (seq == -1)
            break;

        known[seq] = true;
    }
}

void Traverse(int path[], int city, int origin, map<int, int> &seq)
{
    if (city == origin)
    {
        cout << seq.find(city)->second;
        return;
    }

    Traverse(path, path[city], origin, seq);
    cout << " -> " << seq.find(city)->second ;
}

int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}

void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        father[x] = y;
}

bool same(int x, int y)
{
    return find(x) == find(y);
}


double Kruskal(vector<Edge> &edges, bool map[][42])
{
    sort(edges.begin(), edges.end());
    double res = 0;
    int n = edges.size();

    for (int i = 0; i < n; i++) {
        Edge e = edges[i];
        if (!same(e.u, e.v)) {
            map[e.u][e.v] = map[e.v][e.u] = true;
            unite(e.u, e.v);
            res += e.cost;
        }
    }

    return res;
}

int main(int argc, char const *argv[])
{
    int choose = 0;
    while (choose != 5)
    {
        cout << "��ѡ�����²�����" << endl;
        cout << "1 ����̰�ķ���͹����������ʷ�" << endl;
        cout << "2 ����������" << endl;
        cout << "3 ��Դ���·��" << endl;
        cout << "4 ��С������" << endl;
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


                in1.close();
                in2.close();
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            case 2:
            {
                ifstream in("����2.���������������ı�.txt", ios_base::in);
                if (!in.is_open())
                {
                    cout << "Error opening file..." << endl;
                    exit(1);
                }

                char ch;
                int incidence[MAXSIZE] = {0};
                while (in >> ch)
                {
                    if (ch == '#')
                        incidence[0]++;
                    else
                    {
                        ch = tolower(ch);
                        incidence[ch - 'a' + 1]++;
                    }
                }
                pNode Tree = HuffmanTree(incidence);
                cout << "�������������£�" << endl;
                int HuffmanCode = printHuffman(Tree, string(), incidence);
                int OrdinaryCode = 0;
                for (int i = 0; i <= 26; i++)
                    OrdinaryCode += incidence[i] * 5;
                cout << "���ù��������룬�����ı���Ҫ�Ĵ洢������: " << HuffmanCode << endl;
                cout << "���ö������룬�����ı���Ҫ�Ĵ洢������: " << OrdinaryCode << endl;

                in.close();
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            case 3:
            {
                ifstream in1("����1-1.22��վͼ���ڽӾ���-v1.txt", ios_base::in);
                ifstream in2("����1-1.42��վͼ���ڽӾ���-v1.txt", ios_base::in);
                if (!in1.is_open() || !in2.is_open())
                {
                    cout << "Error opening file..." << endl;
                    exit(1);
                }

                map<int, int> mark, seq;
                int enodedID, i = 0;
                double num;
                bool known[42];
                double map[42][42];
                double dist[42];
                int path[42];

                string line;
                getline(in1, line);
                istringstream iss(line);
                while (iss >> enodedID) {
                    mark.insert(make_pair(enodedID, i));
                    seq.insert(make_pair(i++, enodedID));
                }

                for (int i = 0; i < 22; i++) {
                    dist[i] = INT_MAX;
                    for (int j = 0; j <= 22; j++) {
                        in1 >> num;
                        if (j != 0)
                            map[i][j - 1] = num;
                    }
                }
                memset(known, 0, sizeof(known));
                Dijkstra(dist, map, known, mark.find(567443)->second, path, 22);

                cout << "22����վ������ɵ�ͼ: " << endl;
                cout << "567443����������ĵ�Դ���·����" << endl;
                for (int i = 0; i < 22; i++)
                {
                    cout << "567443->" << seq.find(i)->second << ": " << dist[i] << endl;
                }
                cout << "567443��33109�����·����" << endl;
                Traverse(path, mark.find(33109)->second, mark.find(567443)->second, seq);
                cout << endl;

                mark.clear();
                seq.clear();
                getline(in2, line);
                iss.clear();
                iss.str(line);
                i = 0;
                while (iss >> enodedID) {
                    mark.insert(make_pair(enodedID, i));
                    seq.insert(make_pair(i++, enodedID));
                }

                for (int i = 0; i < 42; i++) {
                    dist[i] = INT_MAX;
                    for (int j = 0; j <= 42; j++) {
                        in2 >> num;
                        if (j != 0)
                            map[i][j - 1] = num;
                    }
                }
                memset(known, 0, sizeof(known));
                Dijkstra(dist, map, known, mark.find(565845)->second, path, 42);

                cout << "42����վ������ɵ�ͼ�� " << endl;
                cout << "565845����������ĵ�Դ���·����" << endl;
                for (int i = 0; i < 42; i++)
                {
                    cout << "565845->" << seq.find(i)->second << ": " << dist[i] << endl;
                }
                cout << "565845��565667�����·����" << endl;
                Traverse(path, mark.find(565667)->second, mark.find(565845)->second, seq);
                cout << endl;

				in1.close();
				in2.close();
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
            case 4:
			{
                ifstream in1("����1-1.22��վͼ���ڽӾ���-v1.txt", ios_base::in);
                ifstream in2("����1-1.42��վͼ���ڽӾ���-v1.txt", ios_base::in);
                if (!in1.is_open() || !in2.is_open())
                {
                    cout << "Error opening file..." << endl;
                    exit(1);
                }

                map<int, int> mark, seq;
                int enodedID, i = 0;
                double num;
                bool map[42][42] = {0};
                vector<Edge> edges;

                string line;
                getline(in1, line);
                istringstream iss(line);
                while (iss >> enodedID) {
                    mark.insert(make_pair(enodedID, i));
                    seq.insert(make_pair(i++, enodedID));
                }

                for (int i = 0; i < 22; i++) {
                    father[i] = i;
                    for (int j = 0; j <= 22; j++) {
                        in1 >> num;
                        if (j != 0 && num > 0) {
                            Edge temp;
                            temp.u = i;
                            temp.v = j - 1;
                            temp.cost = num;
                            edges.push_back(temp);
                        }
                    }
                }
                double res = Kruskal(edges, map);
                cout << "22����վ������ɵ�ͼ����С����������Ϊ�� " << res << endl;
                cout << "���ӵı��У�" << endl;
                for (int i = 0; i < 22; i++)
                    for (int j = i + 1; j < 22; j++)
                        if (map[i][j])
                            cout << i + 1 << "--" << j + 1 << '\t';
                cout << endl;

                mark.clear();
                seq.clear();
                edges.clear();
                memset(map, 0, sizeof(map));
                i = 0;

                getline(in2, line);
                iss.str(line);
                while (iss >> enodedID) {
                    mark.insert(make_pair(enodedID, i));
                    seq.insert(make_pair(i++, enodedID));
                }

                for (int i = 0; i < 42; i++) {
                    father[i] = i;
                    for (int j = 0; j <= 42; j++) {
                        in2 >> num;
                        if (j != 0 && num > 0) {
                            Edge temp;
                            temp.u = i;
                            temp.v = j - 1;
                            temp.cost = num;
                            edges.push_back(temp);
                        }
                    }
                }
                res = Kruskal(edges, map);
                cout << "42����վ������ɵ�ͼ����С����������Ϊ�� " << res << endl;
                cout << "���ӵı��У�" << endl;
                for (int i = 0; i < 42; i++)
                    for (int j = i + 1; j < 42; j++)
                        if (map[i][j])
                            cout << i + 1 << "--" << j + 1<< '\t';
                cout << endl;

                in1.close();
                in2.close();
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }

            default:
                break;
        }
    }
    return 0;
}
