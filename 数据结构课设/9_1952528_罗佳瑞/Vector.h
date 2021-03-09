#pragma once
#include<iostream>
using namespace std;
#define MAX_SIZE 50

//队列定义
template<class T>
class Queue {
private:
	int rear, f,count;
	T* elements;
public:
	Queue() :rear(-1), f(0), count(0) { elements = new T[MAX_SIZE]; }
	bool empty() {//判断是否为空
		return count <= 0;
	}
	bool full() {//判断是否已满
		return count >= MAX_SIZE;
	}
	int size() {//返回队列当前大小
		return count;
	}
	void push(T element) {//入队
		if (full()) {
			cerr << "队列已满！" << endl;
			exit(1);
		}
		else {
			rear = (rear + 1) % MAX_SIZE;
			elements[rear] = element;
			count++;
		}
	}
	void pop() {//出队
		if (empty()) {
			cerr << "队列为空" << endl;
			exit(1);
		}
		else {
			f = (f + 1) % MAX_SIZE;
			count--;
		}
	}
	T front() {//取队首元素
		return elements[f];
	}
};

//栈实现
template<class T>
class Stack {
private:
	int t;
	T* elements;
public:
	Stack() :t(-1){ elements = new T[MAX_SIZE]; }
	bool empty() {//判断是否为空
		return t < 0;
	}
	bool full() {//判断是否已满
		return t >= MAX_SIZE;
	}
	int size() {//返回队列当前大小
		return t+1;
	}
	void push(T element) {//入栈
		if (full()) {
			cerr << "栈已满！" << endl;
			exit(1);
		}
		else {
			t++;
			elements[t] = element;
		}
	}
	void pop() {//出队
		if (empty()) {
			cerr << "栈为空" << endl;
			exit(1);
		}
		else {
			t--;
		}
	}
	T top() {//取队首元素
		return elements[t];
	}
};