#include <iostream>
using namespace std;

class edgeNode {//�������߽���ඨ��
public:
	char tail, head;//���������ߵ�������
	float cost;//���������ߵ�Ȩֵ
	void assign(int h, int t, float c) {
		tail = t;head = h; cost = c;
	}
	void operator =(edgeNode& R) { tail = R.tail;head = R.head; cost = R.cost; }
	
	bool operator <(edgeNode& R) { return cost <= R.cost; }
	bool operator >(edgeNode& R) { return cost > R.cost; }
};


class Tree {//�������߽���ඨ��
private:
	edgeNode* root;//��������ͷ���
	int n, m;//�������Ķ�����������
	void create();//��ʼ����
	void print();//��ӡ����
	void add(char element, char* set);//��Ԫ�ؼ��뼯��
	void unite(char** set, int num1, int num2, int setnum);//�ϲ�������
	int subject(char element, char** set, int num);//���Ҹ�Ԫ���Ƿ���ĳ������
	void Keuskal();//Kruskal�㷨������С������
public:
	void run();//���к���
};


int main()
{
	Tree net;
	net.run();
	system("pause");
	return 0;
}
void Tree::run() {
	cout << "**            �������ģ��ϵͳ            **" << endl
		<< "============================================" << endl
		<< "**           A --- ��������               **" << endl
		<< "**           B --- ������С������         **" << endl
		<< "**           C --- ��ʾ��С������         **" << endl
		<< "**           D --- �˳�����               **" << endl
		<< "============================================" << endl
		<< endl;
	while (true) {
		char op;
		cout << "\n��ѡ�����: ";
		cin >> op;
		if (!cin.good()) {//�������
			cin.clear();
			op = -1; 
		}
		cin.ignore(INT32_MAX, '\n');
		switch (op) {
		case 'A':case 'a':create();break;
		case 'B':case 'b':Keuskal();break;
		case 'C':case 'c':print();break;
		case 'D':case 'd':cout << "�����˳�..." << endl;return;
		default:cerr << "������������������!" << endl;break;
		}
	}
}
	
void Tree::create() {//��ʼ����
	cout << "�����붥����Ŀ:" ; //��������Ķ�����Ŀ�ͱ���
	cin >> n;
	cout << "���������Ŀ:" ;
	cin >> m;
	root = new edgeNode[m];
	if (m > 0 && n > 0)//�ж��Ƿ��ǿ���
	{
		for (int i = 0; i < m; i++)//�������˵��Ȩֵ
		{
			cout << "���������������Լ���(�Կո�ָ�������):";
			char head, tail;
			float cost;
			cin >> head >> tail >> cost;
			root[i].assign(head, tail, cost);
		}
	}
	else
	{
		cout << "�������" << endl;
		exit(1);
	}
}
void Tree::print() {
	float sum = 0;
	if (root == NULL)
	{
		cout << "��������С������" << endl;
		exit(1);
	}
	cout << "��С�������Ķ���߼����£�" << endl;
	for (int i = 0;i < n;i++)
	{
		cout << root[i].head << "-><" <<root[i].cost<<">->"<< root[i].tail <<'\t';
		sum += root[i].cost;
	}
	cout << "\n��С�ķ�ֵ��" << sum << endl;
	return;
}

void Tree::Keuskal() {//Kruskal�㷨������С������
	char** node = new char* [n];
	for (int i = 0; i < n; i++)
		node[i] = new char[n];//�����㼯��
	for (int i = 0;i < n;i++)//��������
		for (int j = 0;j < n;j++)
			node[i][j] = 0;
	edgeNode* minTree = new edgeNode[n - 1];//������С��
	int set = 0, count = 0;//�Ǽ�������������ֱ��n-1��
	for (int i = 0;i < m;i++)//��Ȩֵ��������
		for (int j = i;j < m;j++)
			if (root[j] < root[i])
			{
				edgeNode temp;
				temp = root[i];
				root[i] = root[j];
				root[j] = temp;
			}
	for (int i = 0;i < m;i++)
	{
		if (count < n) {
			int h = subject(root[i].head, node, set), t = subject(root[i].tail, node, set);//��������������
			if (h == -1 && t == -1)//���˵�����ڼ����У����½�һ����
			{
				node[set][0] = root[i].head;
				node[set][1] = root[i].tail;
				set++;
				minTree[count] = root[i];
				count++;
			}
			else if (h == t)//���˵���һ������������ñ߼��룬������һ����
				continue;
			else if (h == -1 && t != -1)//һ�˵��ڼ����У���һ�˵㲻�ڣ�����һ�˵����
			{
				add(root[i].head, node[t]);
				minTree[count] = root[i];
				count++;
			}
			else if (h != -1 && t == -1)//һ�˵��ڼ����У���һ�˵㲻�ڣ�����һ�˵����
			{
				add(root[i].tail, node[h]);
				minTree[count] = root[i];
				count++;
			}
			else if (h != -1 && t != -1)//�����˵�ֱ���������������������Ϻϲ�
			{
				unite(node, h, t, set);
				set--;
				minTree[count] = root[i];
				count++;
			}
		}
	}
	if (count == n - 1)
	{
		root = minTree;
		n = count;
	}
	else
		root = NULL;
	cout << "�ѹ�����С��������" << endl;
}
int Tree::subject(char element, char** set, int num) {//������ϵ�ж�
	int i, j;
	for (i = 0;i < num;i++)
		for (j = 0; j < n; j++)
			if (element == set[i][j])//�ж�Ԫ������ĳ������
				return i;//���ؼ������
	return -1;//�������κμ��Ϸ���-1
}
void Tree::add(char element, char* set) {//Ԫ�ؼ��뵽������
	int i;
	for (i = 0;i < n;i++)
		if (set[i] == 0)
		{
			set[i] = element;
			return;
		}
	exit(1);
}
void Tree::unite(char** set, int num1, int num2, int setnum) {//���Ϻϲ�
	int i, j, k, min = (num1 <= num2 ? num1 : num2), max = (num1 > num2 ? num1 : num2);
	for (i = 0;i < n;i++)
		if (set[min][i] == 0)
		{
			for (j = 0;set[max][j] != 0 && j < n;i++, j++)
				set[min][i] = set[max][j];
			for (k = max;k < setnum;k++)
				set[k] = set[k + 1];
			return;
		}
	exit(1);
}