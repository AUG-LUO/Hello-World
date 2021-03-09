#pragma once
#include<iostream>
using namespace std;
#define MAX_SIZE 50

//���ж���
template<class T>
class Queue {
private:
	int rear, f,count;
	T* elements;
public:
	Queue() :rear(-1), f(0), count(0) { elements = new T[MAX_SIZE]; }
	bool empty() {//�ж��Ƿ�Ϊ��
		return count <= 0;
	}
	bool full() {//�ж��Ƿ�����
		return count >= MAX_SIZE;
	}
	int size() {//���ض��е�ǰ��С
		return count;
	}
	void push(T element) {//���
		if (full()) {
			cerr << "����������" << endl;
			exit(1);
		}
		else {
			rear = (rear + 1) % MAX_SIZE;
			elements[rear] = element;
			count++;
		}
	}
	void pop() {//����
		if (empty()) {
			cerr << "����Ϊ��" << endl;
			exit(1);
		}
		else {
			f = (f + 1) % MAX_SIZE;
			count--;
		}
	}
	T front() {//ȡ����Ԫ��
		return elements[f];
	}
};

//ջʵ��
template<class T>
class Stack {
private:
	int t;
	T* elements;
public:
	Stack() :t(-1){ elements = new T[MAX_SIZE]; }
	bool empty() {//�ж��Ƿ�Ϊ��
		return t < 0;
	}
	bool full() {//�ж��Ƿ�����
		return t >= MAX_SIZE;
	}
	int size() {//���ض��е�ǰ��С
		return t+1;
	}
	void push(T element) {//��ջ
		if (full()) {
			cerr << "ջ������" << endl;
			exit(1);
		}
		else {
			t++;
			elements[t] = element;
		}
	}
	void pop() {//����
		if (empty()) {
			cerr << "ջΪ��" << endl;
			exit(1);
		}
		else {
			t--;
		}
	}
	T top() {//ȡ����Ԫ��
		return elements[t];
	}
};