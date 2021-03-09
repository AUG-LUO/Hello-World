#include <iostream>
using namespace std;

class edgeNode {//生成树边结点类定义
public:
	char tail, head;//生成树各边的两顶点
	float cost;//生成树各边的权值
	void assign(int h, int t, float c) {
		tail = t;head = h; cost = c;
	}
	void operator =(edgeNode& R) { tail = R.tail;head = R.head; cost = R.cost; }
	
	bool operator <(edgeNode& R) { return cost <= R.cost; }
	bool operator >(edgeNode& R) { return cost > R.cost; }
};


class Tree {//生成树边结点类定义
private:
	edgeNode* root;//生成树的头结点
	int n, m;//生成树的顶点数、边数
	void create();//初始化树
	void print();//打印函数
	void add(char element, char* set);//将元素加入集合
	void unite(char** set, int num1, int num2, int setnum);//合并两集合
	int subject(char element, char** set, int num);//查找该元素是否在某集合中
	void Keuskal();//Kruskal算法生成最小生成树
public:
	void run();//运行函数
};


int main()
{
	Tree net;
	net.run();
	system("pause");
	return 0;
}
void Tree::run() {
	cout << "**            电网造价模拟系统            **" << endl
		<< "============================================" << endl
		<< "**           A --- 创建电网               **" << endl
		<< "**           B --- 构造最小生成树         **" << endl
		<< "**           C --- 显示最小生成树         **" << endl
		<< "**           D --- 退出程序               **" << endl
		<< "============================================" << endl
		<< endl;
	while (true) {
		char op;
		cout << "\n请选择操作: ";
		cin >> op;
		if (!cin.good()) {//输入错误
			cin.clear();
			op = -1; 
		}
		cin.ignore(INT32_MAX, '\n');
		switch (op) {
		case 'A':case 'a':create();break;
		case 'B':case 'b':Keuskal();break;
		case 'C':case 'c':print();break;
		case 'D':case 'd':cout << "正在退出..." << endl;return;
		default:cerr << "输入有误，请重新输入!" << endl;break;
		}
	}
}
	
void Tree::create() {//初始化树
	cout << "请输入顶点数目:" ; //输入所求的顶点数目和边数
	cin >> n;
	cout << "请输入边数目:" ;
	cin >> m;
	root = new edgeNode[m];
	if (m > 0 && n > 0)//判断是否是空树
	{
		for (int i = 0; i < m; i++)//输入两端点和权值
		{
			cout << "请输入两个顶点以及边(以空格分隔各个数):";
			char head, tail;
			float cost;
			cin >> head >> tail >> cost;
			root[i].assign(head, tail, cost);
		}
	}
	else
	{
		cout << "输入错误" << endl;
		exit(1);
	}
}
void Tree::print() {
	float sum = 0;
	if (root == NULL)
	{
		cout << "不存在最小生成树" << endl;
		exit(1);
	}
	cout << "最小生成树的顶点边及如下：" << endl;
	for (int i = 0;i < n;i++)
	{
		cout << root[i].head << "-><" <<root[i].cost<<">->"<< root[i].tail <<'\t';
		sum += root[i].cost;
	}
	cout << "\n最小耗费值：" << sum << endl;
	return;
}

void Tree::Keuskal() {//Kruskal算法生成最小生成树
	char** node = new char* [n];
	for (int i = 0; i < n; i++)
		node[i] = new char[n];//辅助点集合
	for (int i = 0;i < n;i++)//数组置零
		for (int j = 0;j < n;j++)
			node[i][j] = 0;
	edgeNode* minTree = new edgeNode[n - 1];//建立最小树
	int set = 0, count = 0;//记集合数、边数（直到n-1）
	for (int i = 0;i < m;i++)//按权值将边排序
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
			int h = subject(root[i].head, node, set), t = subject(root[i].tail, node, set);//查找其所属集合
			if (h == -1 && t == -1)//两端点均不在集合中，则新建一集合
			{
				node[set][0] = root[i].head;
				node[set][1] = root[i].tail;
				set++;
				minTree[count] = root[i];
				count++;
			}
			else if (h == t)//两端点在一个集合里，不将该边加入，处理下一条边
				continue;
			else if (h == -1 && t != -1)//一端点在集合中，另一端点不在，则将另一端点加入
			{
				add(root[i].head, node[t]);
				minTree[count] = root[i];
				count++;
			}
			else if (h != -1 && t == -1)//一端点在集合中，另一端点不在，则将另一端点加入
			{
				add(root[i].tail, node[h]);
				minTree[count] = root[i];
				count++;
			}
			else if (h != -1 && t != -1)//两个端点分别在两个集合里，则将两个集合合并
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
	cout << "已构建最小生成树！" << endl;
}
int Tree::subject(char element, char** set, int num) {//从属关系判断
	int i, j;
	for (i = 0;i < num;i++)
		for (j = 0; j < n; j++)
			if (element == set[i][j])//判断元素属于某个集合
				return i;//返回集合序号
	return -1;//不属于任何集合返回-1
}
void Tree::add(char element, char* set) {//元素加入到集合中
	int i;
	for (i = 0;i < n;i++)
		if (set[i] == 0)
		{
			set[i] = element;
			return;
		}
	exit(1);
}
void Tree::unite(char** set, int num1, int num2, int setnum) {//集合合并
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