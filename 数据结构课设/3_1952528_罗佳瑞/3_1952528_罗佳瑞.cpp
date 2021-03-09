#include<iostream>
#include"Vector.h"
using namespace std;

class Point {
private:
	int x0, y0;
public:
	Point() :x0(0), y0(0) {};//Ĭ�Ϲ��캯��
	Point(int a, int b) :x0(a), y0(b) {};//���캯��
	int x() { return x0; }//��ȡ�����ֵ
	int y() { return y0; }
};

int main() {
	//�����Թ�
	int x_size, y_size;
	cout << "�������Թ���С�������ꡢ�����꣩��";
	cin >> x_size >> y_size;
	int** maze = new int* [y_size];//�Թ���ά����
	for (int i = 0; i < y_size; i++)
	{
		maze[i] = new int[x_size];
	}
	for (int i = 0; i < y_size; i++)
		for(int j=0;j<x_size;j++)
	{
		maze[i][j]= 1;
	}
	cout << "�������Թ���"<<endl;
	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++)
			cin >> maze[i][j];
	
	//��������յ�
	int start_x, start_y;
	int end_x, end_y;
	cout << "������������꣨�����ꡢ�����꣩��";
	cin >> start_x >> start_y;
	cout << "�������յ����꣨�����ꡢ�����꣩��";
	cin >> end_x >> end_y;
	
	//Ѱ��·��
	int next[4][2] = { {-1,0} ,{1,0},{0,-1}, {0,1} };//�ƶ����飺��������
	int** mark = new int* [y_size];//������Ƕ�ά����
	for (int i = 0; i < y_size; i++)
	{
		mark[i] = new int[x_size];
	}
	for (int i = 0; i < y_size; i++)
		for (int j = 0;j < x_size;j++)
		{
			mark[i][j] = 0;
		}
	Stack<Point>route;//·��ջ
	Point current(start_x,start_y);
	route.push(current);
	int now_x = 0, now_y = 0;
	while (current.x() != end_x || current.y() != end_y) {
		int k = 0;
		for (;k < 4;k++)//�������ĸ�����̽��
		{
			now_x = current.x() + next[k][0];
			now_y = current.y() + next[k][1];
			if (now_x <0 || now_x >= x_size|| now_y <0 || now_y >= y_size)//�����߽��������һ��̽��
				continue;
			if (maze[now_x][now_y] == 1 && mark[now_x][now_y] == 0)//��Ϊͨ·��δ��̽��������ջ�����Ӵ˴���������̽��
				{
					mark[now_x][now_y] = 1;
					current = Point(now_x, now_y);
					route.push(current);
					break;
				}
		
		}
		if (k == 4)//���ĸ��������ͨ·������ջ����̽��
		{
			route.pop();
			current = route.top();
		}
		if (route.empty()) {//ջ��˵����·��
			cout << "û��·��!" << endl;
			return 0;
		}
	}

	//��ӡ��ͼ
	Stack<Point> copy_route;
	while (!route.empty()) {
		maze[route.top().x()][route.top().y()] = 2;
		copy_route.push(route.top());
		route.pop();
	}
	route = copy_route;

	cout << "�Թ���ͼ ��" << endl;
	for (int j = 0; j < y_size; j++) {
		cout << "\t" << j << "��";
	}
	cout << endl;

	for (int i = 0; i < x_size; i++) {
		cout << i << "��";
		for (int j = 0; j < y_size; j++) {
			switch (maze[i][j]) {
			default:
			case 0:
				cout << "\t#";
				break;
			case 1:
				cout << "\t0";
				break;
			case 2:
				cout << "\tx";
				break;
			}
		}
		cout << endl;
	}

	//��ӡ·��
	cout << "�Թ�·��:" << endl
		<< "(" << start_x << "," << start_y << ")";
	route.pop();
	while (!route.empty()) {
		cout << " ---> "
			<< "(" << route.top().x() << "," << route.top().y() << ")";
		route.pop();
	}
	cout << endl;
	system("pause");
	return 0;
}