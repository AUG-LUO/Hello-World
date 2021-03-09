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
	if (p != NULL)//��Ϊ��ָ��ֱ�ӷ�����һ��ݹ�
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
	Tree(int m) :n(m),head(NULL) {}//���캯��
	~Tree() { delete head; }
	void sort(Node** t, int j); //�ӵ�n����ʼ��������
	void construct_tree(Node** t);  //����������
	void print(); //��ӡ��С����
};


int main()
{
	int n;
	cout<<"������ڵ����(������������):";
	cin>>n;
	int* f = new int[n];
	cout << "������ڵ�(�Կո�ָ�):";
	Node** t = new Node * [n];
	for (int i = 0;i < n;i++)
	{
		cin >> f[i];
		t[i] = new Node(f[i], NULL, NULL);
	}
	Tree T(n);//��ʼ����
	T.construct_tree(t);  //����������
	T.print();
	delete[]t;
	system("pause");
	return 0;
}

void Tree::sort(Node** t, int j)  //�ӵ�n����ʼ��������
{
	int i;
	Node* temp;
	for (i = j;i < n - 1;i++)//���һ��������,ֱ�������ڶ���
		if (t[i]->num > t[i + 1]->num)
		{
			temp = t[i + 1];
			t[i + 1] = t[i];
			t[i] = temp;
		}
}
void Tree::construct_tree(Node** t)  //����������
{
	int i=0;
	for (;i < n - 1;i++)//�ǽ�������
		for (int j=i+1;j < n ;j++)
		if (t[i]->num > t[j]->num)
			swap(t[j]->num, t[i]->num);
	for (i = 1;i < n;i++)
	{
		Node* pt = new Node(t[i - 1]->num + t[i]->num, t[i - 1], t[i]);  //���ɷ�Ҷ�ӽ��Ϊ�ӵ�ǰ��С��ֵ��ʼ�ĺ�ֵ;С��Ϊ����Ů�����Ϊ����Ů
		t[i] = pt;  //�øý���滻��ԭ��Ů���
		sort(t, i);//��������
	}
	head = t[n - 1];
}
void Tree::print(){ //��ӡ��С����
	int minSum=0;
	preorder(head, minSum);
	cout << "��С����Ϊ��"<<minSum << endl;
}