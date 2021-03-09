#pragma once
#include<iostream>
#include"Vector.h"
using namespace std;
class Node {
public:
	Node* next;
	int data;
	Node() : next(NULL), data(-1) {
	}//Ĭ�Ϲ��캯��
	Node(int d) : next(NULL), data(d){
	}//���캯��
};
class Linkedlist {
private:
	Node*first;
	Node*tail;
public:
	Linkedlist() { first =new Node();tail = first; }//���캯��
	void create();//��������
	
	friend void print(Linkedlist* s);//��ӡ����
	friend Linkedlist* compare(Linkedlist&s1,Linkedlist&s2);
};
void Linkedlist::create()//��������
{
	int d;
	cin >> d;
	if (d == -1)
		return;
	Queue<int> data;
	while (d != -1) {//���������ݴ���һ����
		data.push(d);
		cin >> d;
	}
	while (data.empty() == false){//�Ӷ�����ȡ������
		Node* newnode = new Node(data.front());//�����½����������
		data.pop();
		tail->next = newnode;
		tail = newnode;
	}
}

void print(Linkedlist* s)
	{
		if (s == NULL)//�������ָ���ӡNULL
		{
			cout << "NULL";
			return;
		}
		Node* current = s->first->next;
		while (current != NULL)
		{
			cout << current->data;
			current = current->next;
			if (current != NULL)
				cout << ' ';
		}
	}
Linkedlist* compare(Linkedlist& s1,Linkedlist& s2) {
	Node* current1 = s1.first->next;
	Node* current2 = s2.first->next;
	Linkedlist* s3=new Linkedlist();
	if (current1 == NULL || current2 == NULL)//��һ����Ϊ�ս���Ϊ��
		return NULL;
	while (current1 != NULL && current2 != NULL)
	{
		if (current1->data < current2->data)
			current1 = current1->next;
		else if (current1->data > current2->data)//����С����������
			current2 = current2->next;
		else
		{
			Node* newnode = new Node(current1->data);
			s3->tail->next = newnode;
			s3->tail= newnode;
			current1 = current1->next;
			current2 = current2->next;
		}
	}
	if (s3->first->next == NULL)//����Ϊ�գ����ؿ�ָ��
		return NULL;
	return s3;
}
