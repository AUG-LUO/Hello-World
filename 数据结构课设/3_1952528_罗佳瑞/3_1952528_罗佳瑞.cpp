#include<iostream>
#include"Vector.h"
using namespace std;

class Point {
private:
	int x0, y0;
public:
	Point() :x0(0), y0(0) {};//默认构造函数
	Point(int a, int b) :x0(a), y0(b) {};//构造函数
	int x() { return x0; }//调取坐标的值
	int y() { return y0; }
};

int main() {
	//创建迷宫
	int x_size, y_size;
	cout << "请输入迷宫大小（横坐标、纵坐标）：";
	cin >> x_size >> y_size;
	int** maze = new int* [y_size];//迷宫二维数组
	for (int i = 0; i < y_size; i++)
	{
		maze[i] = new int[x_size];
	}
	for (int i = 0; i < y_size; i++)
		for(int j=0;j<x_size;j++)
	{
		maze[i][j]= 1;
	}
	cout << "请输入迷宫："<<endl;
	for (int i = 0; i < x_size; i++)
		for (int j = 0; j < y_size; j++)
			cin >> maze[i][j];
	
	//输入起点终点
	int start_x, start_y;
	int end_x, end_y;
	cout << "请输入起点坐标（横坐标、纵坐标）：";
	cin >> start_x >> start_y;
	cout << "请输入终点坐标（横坐标、纵坐标）：";
	cin >> end_x >> end_y;
	
	//寻找路径
	int next[4][2] = { {-1,0} ,{1,0},{0,-1}, {0,1} };//移动数组：上下左右
	int** mark = new int* [y_size];//辅助标记二维数组
	for (int i = 0; i < y_size; i++)
	{
		mark[i] = new int[x_size];
	}
	for (int i = 0; i < y_size; i++)
		for (int j = 0;j < x_size;j++)
		{
			mark[i][j] = 0;
		}
	Stack<Point>route;//路径栈
	Point current(start_x,start_y);
	route.push(current);
	int now_x = 0, now_y = 0;
	while (current.x() != end_x || current.y() != end_y) {
		int k = 0;
		for (;k < 4;k++)//依次向四个方向探索
		{
			now_x = current.x() + next[k][0];
			now_y = current.y() + next[k][1];
			if (now_x <0 || now_x >= x_size|| now_y <0 || now_y >= y_size)//若出边界则进行下一次探索
				continue;
			if (maze[now_x][now_y] == 1 && mark[now_x][now_y] == 0)//若为通路且未被探索过则入栈，并从此处继续向下探索
				{
					mark[now_x][now_y] = 1;
					current = Point(now_x, now_y);
					route.push(current);
					break;
				}
		
		}
		if (k == 4)//若四个方向均无通路，则退栈回溯探索
		{
			route.pop();
			current = route.top();
		}
		if (route.empty()) {//栈空说明无路径
			cout << "没有路径!" << endl;
			return 0;
		}
	}

	//打印地图
	Stack<Point> copy_route;
	while (!route.empty()) {
		maze[route.top().x()][route.top().y()] = 2;
		copy_route.push(route.top());
		route.pop();
	}
	route = copy_route;

	cout << "迷宫地图 ：" << endl;
	for (int j = 0; j < y_size; j++) {
		cout << "\t" << j << "列";
	}
	cout << endl;

	for (int i = 0; i < x_size; i++) {
		cout << i << "行";
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

	//打印路径
	cout << "迷宫路径:" << endl
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