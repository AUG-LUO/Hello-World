#pragma once
#include<iostream>
#include"Vector.h"
using namespace std;
class Node {
public:
	Node* next;
	int data;
	Node() : next(NULL), data(-1) {
	}//默认构造函数
	Node(int d) : next(NULL), data(d){
	}//构造函数
};
class Linkedlist {
private:
	Node*first;
	Node*tail;
public:
	Linkedlist() { first =new Node();tail = first; }//构造函数
	void create();//创建链表
	
	friend void print(Linkedlist* s);//打印链表
	friend Linkedlist* compare(Linkedlist&s1,Linkedlist&s2);
};
void Linkedlist::create()//创建链表
{
	int d;
	cin >> d;
	if (d == -1)
		return;
	Queue<int> data;
	while (d != -1) {//将输入数据存入一队列
		data.push(d);
		cin >> d;
	}
	while (data.empty() == false){//从队列中取出数据
		Node* newnode = new Node(data.front());//创建新结点链入链表
		data.pop();
		tail->next = newnode;
		tail = newnode;
	}
}

void print(Linkedlist* s)
	{
		if (s == NULL)//若传入空指针打印NULL
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
	if (current1 == NULL || current2 == NULL)//任一链表为空交集为空
		return NULL;
	while (current1 != NULL && current2 != NULL)
	{
		if (current1->data < current2->data)
			current1 = current1->next;
		else if (current1->data > current2->data)//将较小链沿链后移
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
	if (s3->first->next == NULL)//交集为空，返回空指针
		return NULL;
	return s3;
}
