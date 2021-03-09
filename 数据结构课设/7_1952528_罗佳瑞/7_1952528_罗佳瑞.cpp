#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Node
{
public:
	int num;
	Node* Lnode;
	Node* Rnode;
	Node() :num(-1),Lnode(NULL),Rnode(NULL){}
	Node(int n,Node*L,Node*R) :num(n), Lnode(L), Rnode(R) {}
	friend void preorder(Node* p,int &sum);
};
void preorder(Node* p,int&sum)
{
	if (p != NULL)//若为空指针直接返回上一层递归
	{
		if (p->Lnode != NULL&&p->Rnode!=NULL)
			sum += p->num;
		preorder(p->Lnode,sum);
		preorder(p->Rnode,sum);
	}
}



class Tree
{
private:
	int n;
	Node* head;
public:
	Tree(int m) :n(m),head(NULL) {}//构造函数
	~Tree() { delete head; }
	void sort(Node** t, int j); //从第n个开始调整序列
	void construct_tree(Node** t);  //生成最优树
	void print(); //打印最小费用
};


int main()
{
	int n;
	cout<<"请输入节点个数(必须是正整数):";
	cin>>n;
	int* f = new int[n];
	cout << "请输入节点(以空格分隔):";
	Node** t = new Node * [n];
	for (int i = 0;i < n;i++)
	{
		cin >> f[i];
		t[i] = new Node(f[i], NULL, NULL);
	}
	Tree T(n);//初始化树
	T.construct_tree(t);  //生成最优树
	T.print();
	delete[]t;
	system("pause");
	return 0;
}

void Tree::sort(Node** t, int j)  //从第n个开始调整序列
{
	int i;
	Node* temp;
	for (i = j;i < n - 1;i++)//与后一个树调整,直至倒数第二个
		if (t[i]->num > t[i + 1]->num)
		{
			temp = t[i + 1];
			t[i + 1] = t[i];
			t[i] = temp;
		}
}
void Tree::construct_tree(Node** t)  //生成最优树
{
	int i=0;
	for (;i < n - 1;i++)//非降序排序
		for (int j=i+1;j < n ;j++)
		if (t[i]->num > t[j]->num)
			swap(t[j]->num, t[i]->num);
	for (i = 1;i < n;i++)
	{
		Node* pt = new Node(t[i - 1]->num + t[i]->num, t[i - 1], t[i]);  //生成非叶子结点为从当前最小两值开始的和值;小的为左子女，大的为右子女
		t[i] = pt;  //用该结点替换掉原子女结点
		sort(t, i);//调整序列
	}
	head = t[n - 1];
}
void Tree::print(){ //打印最小费用
	int minSum=0;
	preorder(head, minSum);
	cout << "最小花费为："<<minSum << endl;
}