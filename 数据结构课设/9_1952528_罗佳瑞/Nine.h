#pragma once
#include<iostream>
#include<fstream>
#include<iomanip>
#include"Vector.h"
#define N 8//ѧ����
#define n 38//�γ���
#define m 2//���޿���
using namespace std;

class course {
public:
	string num, name;//��š�����
	char precourse[10];//���޿γ�
	int period;//��ʱ
	int term;//����ʱ��
	int weekday, time;//���ڡ�ʱ��
	int auxpre[m];//���޿��������
	course() :period(0),term(0),weekday(0),time(0){//���캯��
		for (int i = 0; i < m; i++)
			auxpre[i] = -1;
	}
	bool have_pre();//�Ƿ������޿�
	void pre(string* aux);//���޿δ���
};
class week {
public:
	int day[6][11];//0��ÿ��Ŀγ��������
	int day2 [6];//0��ÿ�����ڿ����ϵĿ�
	int day3 [6];//0��ÿ�����ڿ����ϵĿ�
	week() {//���캯��
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
	int termNum[N];//ÿѧ�ڵĿγ�����
	int termDegree[n];//ÿ�ÿε����ȼ�
	course classes[n];//���пγ̰��������
	Queue<int>termClass[N];//�˸�ѧ�ڵĿγ̶���
	week termWeek[N];//�˸�ѧ�ڵ��ܿα�
public:
	schedule() {//���캯��
		for (int i = 0; i < n; i++)
		{
			termDegree[i] = 0;
		}
	}
	void putIn();//���ļ�������γ���Ϣ
	void arrangeTerm();//���ſγ�����ѧ��
	void tweekDegree(int t, int c, int sort);//ѧ�������γ���ţ����ݴ������ȷ�ʽѡ��
	void tWeek(int t);//����tѧ�ڵ��ܿγ̱�
	void arrangeWeek();//���Ű˸�ѧ�ڵ��ܿα�
	void print();//����α��ļ���
			
};
bool course::have_pre() {//�Ƿ������޿�
	string temp = "x";
	if (precourse == temp)
		return false;
	return true;
}
void course::pre(string* aux) {//���޿δ���
	int i = 0;
	for (int j = 0;precourse[j] != '\0';j++)
	{
		if (precourse[j] == ',')//�����޿ζϳɶ��int��
		{
			i++;
			continue;
		}
		aux[i] += precourse[j];
	}
}

void schedule::putIn() {//���ļ�������γ���Ϣ
	fstream infile("IN.txt", ios::in);
	if (infile.is_open() == 0) {
		cerr << "�����ļ���ʧ�ܣ�" << endl;
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
void schedule::arrangeTerm() {//���ſγ�����ѧ��
	for (int i = 0;i < n;i++) {
		if (classes[i].term != 0)//�����й涨ѧ��
		{
			termDegree[i] = -1;
			termClass[classes[i].term - 1].push(i);//��������ȼ���-1
		}
		else if (classes[i].have_pre() == false) {//�������޿γ�Ҫ��
			termDegree[i] = 0;
		}
		else if (classes[i].have_pre() == true)
		{
			string* aux = new string[m];
			classes[i].pre(aux);
			for (int j = 0;j < m;j++) //�����������м�¼�����޿ε����¼��
				for (int t = 0;t < n;t++)
					if (aux[j] == classes[t].num)
					{
						classes[i].auxpre[j] = t;
						break;
					}
		}
	}
	for (int i = 0;i < n;i++) {
		if (classes[i].auxpre[0] != -1)//���������޿εĿγ�
		{
			int temp[m] = { 1 };//�����޿ε����ȼ�ĿǰΪ1
			for (int j = 0;j < m && classes[i].auxpre[j] != -1;j++)
				temp[j] += termDegree[classes[i].auxpre[j]];//����ÿ�����޿�·�����м��ڿ�
			int max = 0;
			for (int j = 1;j < m && classes[i].auxpre[j] != -1;j++)//ȡ���������
				if (temp[j] > temp[max])
					max = j;
			termDegree[i] = temp[max];
		}
	}
	for (int i = 0;i < N;i++) {
		int temp = 0;
		while (termClass[i].size() < termNum[i]) {//ÿ��ѧ�ڵĿγ�������������Ҫ��
			for (int j = 0;j < n && termClass[i].size() < termNum[i];j++)
			{
				if (termDegree[j] == temp)//�����ȼ���������ʱ�����ÿ���ż����ѧ�ڶ���
				{
					termClass[i].push(j);
					classes[j].term = i;
					termDegree[j] = -1;//��������ȼ���-1
				}
			}
			if (termClass[i].size() == termNum[i])//�������˳�ѭ��
				break;
			temp++;
			if (temp > i)//���������ȼ��Ѵ��ڵ�ǰѧ�ڣ����ѧ���޷�������Ӧ����
			{
				cerr << "��" << i + 1 << "ѧ�ڰ��ſγ�������������Ŀγ�����" << endl;
				exit(1);
			}
		}
	}
}
void schedule::tweekDegree(int t, int c, int sort) {//ѧ�������γ���ţ����ݴ������ȷ�ʽѡ��
	if (sort == 3 && classes[c].period == 3) {//��������ʱ����
		const int dayDegree[5] = { 3,2,4,5,1 };//ÿ�찲�Ÿÿε����ȼ�����
		for (int i = 0; i < 5; i++) {
			if (termWeek[t].day3[dayDegree[i]] < 2) {//���ÿη�����[dayDegree[i]]�α��������Ͽ�ʱ�����
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
	else if (sort == 3) {//�������ȣ���5/6��ʱ�������
		const int dayDegree[5] = { 1,5,4,2,3 };
		for (int i = 0; i < 4; i++) {
			if (termWeek[t].day3[dayDegree[i]] < 2) {//���������������ÿη�����[dayDegree[i]]�α��������Ͽ�ʱ�����
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
		for (int i = 0; i < 5; i++) {//������������޷����������������
			if (termWeek[t].day3[dayDegree[i]] < 2) {//���������ÿη�����[dayDegree[i]]�α��������Ͽ�ʱ�����
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
	else {//����ʱΪ4
		const int dayDegree[5] = { 5,1,2,4,3 };
		for (int i = 0; i < 4; i++) {
			if (termWeek[t].day2[dayDegree[i]] < 2) {
				switch (dayDegree[i]) {
				case 1:classes[c].weekday = 4;break;
				case 4:classes[c].weekday = 2;break;
				case 2:classes[c].weekday = 5;break;
				case 5:classes[c].weekday = 1;break;
				}
				if (termWeek[t].day2[dayDegree[i]] < 2 && termWeek[t].day2[classes[c].weekday] < 2) {//���������������ÿη�����[dayDegree[i]]�α��������Ͽ�ʱ�����
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
		for (int i = 0; i < 5; i++) {//���޷����������������
			if (termWeek[t].day2[dayDegree[i]] < 2) {
				for (int j = 1;j <= 5;j++) {
					if (j == dayDegree[i])
						continue;
					if (termWeek[t].day2[j] < 2) {//���������ÿη�����[dayDegree[i]]�α��������Ͽ�ʱ�����
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
void schedule::tWeek(int t) {//����tѧ�ڵ��ܿγ̱�
	int size = termNum[t];
	int* temp = new int[size];
	for (int i = 0;i < size;i++)//ȡ����ѧ�ڿγ̣���ȷ��ÿ���γ������Ͽ�����
	{
		temp[i] = termClass[t].front();
		termClass[t].pop();
	}
	for (int i = 0;i < size;i++) {
		if (classes[temp[i]].period == 3) //�ÿγ����ڿ���������
			tweekDegree(t, temp[i], 3);
	}
	for (int i = 0;i < size;i++) {
		if (classes[temp[i]].period == 5 || classes[temp[i]].period == 6)//�ÿγ̿�ʱ��Ϊ5��6��������3��
			tweekDegree(t, temp[i], 3);
	}
	for (int i = 0;i < size;i++) {
		if (classes[temp[i]].period == 4)//�ÿγ̿�ʱ��Ϊ5��6��������2��
			tweekDegree(t, temp[i], 2);
	}
}
void schedule::arrangeWeek() {//���Ű˸�ѧ�ڵ��ܿα�
	for (int i = 0;i < N;i++)
		tWeek(i);
}
void schedule::print() {//����α��ļ���
	fstream outfile("OUT.txt", ios::out);
	if (outfile.is_open() == 0) {
		cerr << "����ļ���ʧ�ܣ�" << endl;
		exit(1);
	}
	outfile << "��ӡ�α����£�" << endl;
	for (int i = 0; i < N; i++) {
		outfile << "��" << i + 1 << "ѧ�ڿα����£�" << endl;
		outfile << "\t  ";
		for (int j = 0; j < 5; j++)
		{
			outfile << setiosflags(ios::fixed) << setiosflags(ios::left);
			outfile << "����" << setw(12) << j + 1;
		}
		outfile << endl;
		for (int j = 1;j < 11;j++) {
			if (j == 10)
				outfile << "��" << j << "�ڿΣ�";
			else
				outfile << "�� " << j << "�ڿΣ�";
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