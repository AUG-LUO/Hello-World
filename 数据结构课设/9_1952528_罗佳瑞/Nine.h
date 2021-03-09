#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
#include"Vector.h"
#define N 8//学期数
#define n 38//课程数
#define m 2//先修课数
using namespace std;

class course {
public:
	string num, name;//序号、名称
	char precourse[10];//先修课程
	int period;//课时
	int term;//开设时间
	int weekday, time;//星期、时间
	int auxpre[m];//先修课序号数组
	course() :period(0),term(0),weekday(0),time(0){//构造函数
		for (int i = 0; i < m; i++)
			auxpre[i] = -1;
	}
	bool have_pre();//是否有先修课
	void pre(string* aux);//先修课处理
};
class week {
public:
	int day[6][11];//0！每天的课程序号数组
	int day2 [6];//0！每天两节课连上的课
	int day3 [6];//0！每天三节课连上的课
	week() {//构造函数
		for (int i = 0; i < 6; i++){
			day2[i] = 0;
			day3[i] = 0;
			for (int j = 0;j < 11; j++)
			{
				day[i][j] = -1;
			}
		}
	}
};
class schedule {
private:
	int termNum[N];//每学期的课程数量
	int termDegree[n];//每堂课的优先级
	course classes[n];//所有课程按序号数组
	Queue<int>termClass[N];//八个学期的课程队列
	week termWeek[N];//八个学期的周课表
public:
	schedule() {//构造函数
		for (int i = 0; i < n; i++)
		{
			termDegree[i] = 0;
		}
	}
	void putIn();//从文件中输入课程信息
	void arrangeTerm();//安排课程所在学期
	void tweekDegree(int t, int c, int sort);//学期数，课程序号，根据传入优先方式选择
	void tWeek(int t);//安排t学期的周课程表
	void arrangeWeek();//安排八个学期的周课表
	void print();//输出课表到文件中
			
};
bool course::have_pre() {//是否有先修课
	string temp = "x";
	if (precourse == temp)
		return false;
	return true;
}
void course::pre(string* aux) {//先修课处理
	int i = 0;
	for (int j = 0;precourse[j] != '\0';j++)
	{
		if (precourse[j] == ',')//将先修课断成多个int型
		{
			i++;
			continue;
		}
		aux[i] += precourse[j];
	}
}

void schedule::putIn() {//从文件中输入课程信息
	fstream infile("IN.txt", ios::in);
	if (infile.is_open() == 0) {
		cerr << "输入文件打开失败！" << endl;
		exit(1);
	}
	for (int i = 0;i < N; i++)
	{
		infile >> termNum[i];
	}
	for (int i = 0;i < n; i++)
	{
		infile >> classes[i].num >> classes[i].name >> classes[i].period >> classes[i].term >> classes[i].precourse;
	}
	infile.close();
}
void schedule::arrangeTerm() {//安排课程所在学期
	for (int i = 0;i < n;i++) {
		if (classes[i].term != 0)//若已有规定学期
		{
			termDegree[i] = -1;
			termClass[classes[i].term - 1].push(i);//加入后优先级置-1
		}
		else if (classes[i].have_pre() == false) {//若无先修课程要求
			termDegree[i] = 0;
		}
		else if (classes[i].have_pre() == true)
		{
			string* aux = new string[m];
			classes[i].pre(aux);
			for (int j = 0;j < m;j++) //将辅助数组中记录的先修课的序号录入
				for (int t = 0;t < n;t++)
					if (aux[j] == classes[t].num)
					{
						classes[i].auxpre[j] = t;
						break;
					}
		}
	}
	for (int i = 0;i < n;i++) {
		if (classes[i].auxpre[0] != -1)//处理有先修课的课程
		{
			int temp[m] = { 1 };//有先修课的优先级目前为1
			for (int j = 0;j < m && classes[i].auxpre[j] != -1;j++)
				temp[j] += termDegree[classes[i].auxpre[j]];//计算每条先修课路径上有几节课
			int max = 0;
			for (int j = 1;j < m && classes[i].auxpre[j] != -1;j++)//取出大的那条
				if (temp[j] > temp[max])
					max = j;
			termDegree[i] = temp[max];
		}
	}
	for (int i = 0;i < N;i++) {
		int temp = 0;
		while (termClass[i].size() < termNum[i]) {//每个学期的课程数不超过输入要求
			for (int j = 0;j < n && termClass[i].size() < termNum[i];j++)
			{
				if (termDegree[j] == temp)//当优先级条件满足时，将该课序号加入该学期队列
				{
					termClass[i].push(j);
					classes[j].term = i;
					termDegree[j] = -1;//加入后优先级置-1
				}
			}
			if (termClass[i].size() == termNum[i])//加满则退出循环
				break;
			temp++;
			if (temp > i)//若加入优先级已大于当前学期，则该学期无法加满，应报错！
			{
				cerr << "第" << i + 1 << "学期安排课程数不合理，请更改课程数！" << endl;
				exit(1);
			}
		}
	}
}
void schedule::tweekDegree(int t, int c, int sort) {//学期数，课程序号，根据传入优先方式选择
	if (sort == 3 && classes[c].period == 3) {//优先三课时安排
		const int dayDegree[5] = { 3,2,4,5,1 };//每天安排该课的优先级序列
		for (int i = 0; i < 5; i++) {
			if (termWeek[t].day3[dayDegree[i]] < 2) {//将该课放入周[dayDegree[i]]课表，并将其上课时间填好
				classes[c].weekday = dayDegree[i];
				switch (termWeek[t].day3[dayDegree[i]]) {
				case 0:classes[c].time = 2;
					termWeek[t].day3[dayDegree[i]]++;
					termWeek[t].day[dayDegree[i]][3] = c;
					termWeek[t].day[dayDegree[i]][4] = c;
					termWeek[t].day[dayDegree[i]][5] = c;break;
				case 1:classes[c].time = 4;
					termWeek[t].day3[dayDegree[i]]++;
					termWeek[t].day[dayDegree[i]][8] = c;
					termWeek[t].day[dayDegree[i]][9] = c;
					termWeek[t].day[dayDegree[i]][10] = c;break;
				}
				return;
			}
		}
	}
	else if (sort == 3) {//三节优先，分5/6课时两种情况
		const int dayDegree[5] = { 1,5,4,2,3 };
		for (int i = 0; i < 4; i++) {
			if (termWeek[t].day3[dayDegree[i]] < 2) {//若隔两天允许，将该课放入周[dayDegree[i]]课表，并将其上课时间填好
				switch (dayDegree[i]) {
				case 1:classes[c].weekday = 4;break;
				case 4:classes[c].weekday = 1;break;
				case 2:classes[c].weekday = 5;break;
				case 5:classes[c].weekday = 1;break;
				}
				if ((classes[c].period == 6 && termWeek[t].day3[classes[c].weekday] < 2) || (classes[c].period == 5 && termWeek[t].day2[classes[c].weekday] < 2)) {
					switch (termWeek[t].day3[dayDegree[i]]) {
					case 0:classes[c].time = 2;
						termWeek[t].day3[dayDegree[i]]++;
						termWeek[t].day[dayDegree[i]][3] = c;
						termWeek[t].day[dayDegree[i]][4] = c;
						termWeek[t].day[dayDegree[i]][5] = c;break;
					case 1:classes[c].time = 4;
						termWeek[t].day3[dayDegree[i]]++;
						termWeek[t].day[dayDegree[i]][8] = c;
						termWeek[t].day[dayDegree[i]][9] = c;
						termWeek[t].day[dayDegree[i]][10] = c;break;
					}
					if (classes[c].period == 6)
						switch (termWeek[t].day3[classes[c].weekday]) {
						case 0:classes[c].time = 2;
							termWeek[t].day3[classes[c].weekday]++;
							termWeek[t].day[classes[c].weekday][3] = c;
							termWeek[t].day[classes[c].weekday][4] = c;
							termWeek[t].day[classes[c].weekday][5] = c;break;
						case 1:classes[c].time = 4;
							termWeek[t].day3[classes[c].weekday]++;
							termWeek[t].day[classes[c].weekday][8] = c;
							termWeek[t].day[classes[c].weekday][9] = c;
							termWeek[t].day[classes[c].weekday][10] = c;break;
						}
					else
						switch (termWeek[t].day2[classes[c].weekday]) {
						case 0:classes[c].time = 1;
							termWeek[t].day2[classes[c].weekday]++;
							termWeek[t].day[classes[c].weekday][1] = c;
							termWeek[t].day[classes[c].weekday][2] = c;break;
						case 1:classes[c].time = 3;
							termWeek[t].day2[classes[c].weekday]++;
							termWeek[t].day[classes[c].weekday][6] = c;
							termWeek[t].day[classes[c].weekday][7] = c;break;
						}
					return;
				}
			}
		}
		for (int i = 0; i < 5; i++) {//若所有情况都无法满足间隔两天的条件
			if (termWeek[t].day3[dayDegree[i]] < 2) {//若允许，将该课放入周[dayDegree[i]]课表，并将其上课时间填好
				for (int j = 1;j <= 5;j++) {
					if (j == dayDegree[i])
						continue;
					if ((classes[c].period == 6 && termWeek[t].day3[j] < 2) || (classes[c].period == 5 && termWeek[t].day2[j] < 2)) {
						switch (termWeek[t].day3[dayDegree[i]]) {
						case 0:classes[c].time = 2;
							termWeek[t].day3[dayDegree[i]]++;
							termWeek[t].day[dayDegree[i]][3] = c;
							termWeek[t].day[dayDegree[i]][4] = c;
							termWeek[t].day[dayDegree[i]][5] = c;break;
						case 1:classes[c].time = 4;
							termWeek[t].day3[dayDegree[i]]++;
							termWeek[t].day[dayDegree[i]][8] = c;
							termWeek[t].day[dayDegree[i]][9] = c;
							termWeek[t].day[dayDegree[i]][10] = c;break;
						}
						if (classes[c].period == 6)
							switch (termWeek[t].day3[j]) {
							case 0:classes[c].time = 2;
								termWeek[t].day3[j]++;
								termWeek[t].day[j][3] = c;
								termWeek[t].day[j][4] = c;
								termWeek[t].day[j][5] = c;break;
							case 1:classes[c].time = 4;
								termWeek[t].day3[j]++;
								termWeek[t].day[j][8] = c;
								termWeek[t].day[j][9] = c;
								termWeek[t].day[j][10] = c;break;
							}
						else
							switch (termWeek[t].day2[j]) {
							case 0:classes[c].time = 1;
								termWeek[t].day2[j]++;
								termWeek[t].day[j][1] = c;
								termWeek[t].day[j][2] = c;break;
							case 1:classes[c].time = 3;
								termWeek[t].day2[j]++;
								termWeek[t].day[j][6] = c;
								termWeek[t].day[j][7] = c;break;
							}
						return;
					}
				}
			}
		}

	}
	else {//若课时为4
		const int dayDegree[5] = { 5,1,2,4,3 };
		for (int i = 0; i < 4; i++) {
			if (termWeek[t].day2[dayDegree[i]] < 2) {
				switch (dayDegree[i]) {
				case 1:classes[c].weekday = 4;break;
				case 4:classes[c].weekday = 2;break;
				case 2:classes[c].weekday = 5;break;
				case 5:classes[c].weekday = 1;break;
				}
				if (termWeek[t].day2[dayDegree[i]] < 2 && termWeek[t].day2[classes[c].weekday] < 2) {//若隔两天允许，将该课放入周[dayDegree[i]]课表，并将其上课时间填好
					switch (termWeek[t].day2[dayDegree[i]]) {
					case 0:classes[c].time = 1;
						termWeek[t].day2[dayDegree[i]]++;
						termWeek[t].day[dayDegree[i]][1] = c;
						termWeek[t].day[dayDegree[i]][2] = c;break;
					case 1:classes[c].time = 3;
						termWeek[t].day2[dayDegree[i]]++;
						termWeek[t].day[dayDegree[i]][6] = c;
						termWeek[t].day[dayDegree[i]][7] = c;break;
					}
					switch (termWeek[t].day2[classes[c].weekday]) {
					case 0:classes[c].time = 1;
						termWeek[t].day2[classes[c].weekday]++;
						termWeek[t].day[classes[c].weekday][1] = c;
						termWeek[t].day[classes[c].weekday][2] = c;break;
					case 1:classes[c].time = 3;
						termWeek[t].day2[classes[c].weekday]++;
						termWeek[t].day[classes[c].weekday][6] = c;
						termWeek[t].day[classes[c].weekday][7] = c;break;
					}
					return;
				}
			}
		}
		for (int i = 0; i < 5; i++) {//若无法满足间隔两天的条件
			if (termWeek[t].day2[dayDegree[i]] < 2) {
				for (int j = 1;j <= 5;j++) {
					if (j == dayDegree[i])
						continue;
					if (termWeek[t].day2[j] < 2) {//若允许，将该课放入周[dayDegree[i]]课表，并将其上课时间填好
						switch (termWeek[t].day2[dayDegree[i]]) {
						case 0:classes[c].time = 1;
							termWeek[t].day2[dayDegree[i]]++;
							termWeek[t].day[dayDegree[i]][1] = c;
							termWeek[t].day[dayDegree[i]][2] = c;break;
						case 1:classes[c].time = 3;
							termWeek[t].day2[dayDegree[i]]++;
							termWeek[t].day[dayDegree[i]][6] = c;
							termWeek[t].day[dayDegree[i]][7] = c;break;
						}
						switch (termWeek[t].day2[j]) {
						case 0:classes[c].time = 1;
							termWeek[t].day2[j]++;
							termWeek[t].day[j][1] = c;
							termWeek[t].day[j][2] = c;break;
						case 1:classes[c].time = 3;
							termWeek[t].day2[j]++;
							termWeek[t].day[j][6] = c;
							termWeek[t].day[j][7] = c;break;
						}
						return;
					}
				}
			}
		}
	}
}
void schedule::tWeek(int t) {//安排t学期的周课程表
	int size = termNum[t];
	int* temp = new int[size];
	for (int i = 0;i < size;i++)//取出本学期课程，并确定每个课程所需上课天数
	{
		temp[i] = termClass[t].front();
		termClass[t].pop();
	}
	for (int i = 0;i < size;i++) {
		if (classes[temp[i]].period == 3) //该课程三节课连上优先
			tweekDegree(t, temp[i], 3);
	}
	for (int i = 0;i < size;i++) {
		if (classes[temp[i]].period == 5 || classes[temp[i]].period == 6)//该课程课时数为5或6，则优先3节
			tweekDegree(t, temp[i], 3);
	}
	for (int i = 0;i < size;i++) {
		if (classes[temp[i]].period == 4)//该课程课时数为5或6，则优先2节
			tweekDegree(t, temp[i], 2);
	}
}
void schedule::arrangeWeek() {//安排八个学期的周课表
	for (int i = 0;i < N;i++)
		tWeek(i);
}
void schedule::print() {//输出课表到文件中
	fstream outfile("OUT.txt", ios::out);
	if (outfile.is_open() == 0) {
		cerr << "输出文件打开失败！" << endl;
		exit(1);
	}
	outfile << "打印课表如下：" << endl;
	for (int i = 0; i < N; i++) {
		outfile << "第" << i + 1 << "学期课表如下：" << endl;
		outfile << "\t  ";
		for (int j = 0; j < 5; j++)
		{
			outfile << setiosflags(ios::fixed) << setiosflags(ios::left);
			outfile << "星期" << setw(12) << j + 1;
		}
		outfile << endl;
		for (int j = 1;j < 11;j++) {
			if (j == 10)
				outfile << "第" << j << "节课：";
			else
				outfile << "第 " << j << "节课：";
			for (int k = 1;k < 6;k++) {
				if (termWeek[i].day[k][j] != -1)
				{
					outfile << setiosflags(ios::fixed) << setiosflags(ios::left);
					outfile << setw(16) << classes[termWeek[i].day[k][j]].name;
				}
				else
					outfile << setw(16) << " ";
			}
			outfile << endl;
		}
		outfile << endl;
	}
	outfile.close();
}