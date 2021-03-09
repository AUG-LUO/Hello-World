#include<iostream>
#include"Vector.h"
#include <cstring>
#include<cmath>
using namespace std;
int isp(char op);//ջ��������
int icp(char op);//ջ��������
string postfix();//����׺���ʽתΪ��׺���ʽ

bool get(Stack<double>& num, double& left, double& right); //�Ӳ�����ջ��ȡ������������
void Doperator(Stack<double>& num, char op);//�������

int main() {
	cout << "��ӭʹ����������\n��������Ҫ����ı��ʽ����=��β����" << endl;
	string s;
	Stack<double>operand;
	s=postfix();
	for (int i = 0; s[i] != '='; i++)
		if (isdigit(s[i]))
			operand.push((double)s[i] - (double)'0');
		else
			Doperator(operand, s[i]);
	cout << "������Ϊ��" << operand.top()<<endl;
	while (!operand.empty())
		operand.pop();
	system("pause");
	return 0;
}
int isp(char op) {//ջ��������
	switch (op)
	{
	case '+':return 3;break;
	case '-':return 3;break;
	case '*':return 5;break;
	case '/':return 5;break;
	case '%':return 5;break;
	case '^':return 7;break;
	case '(':return 1;break;
	case ')':return 8;break;
	case '=':return 0;break;
	}
}
int icp(char op) {//ջ��������
	switch (op)
	{
	case '+':return 2;break;
	case '-':return 2;break;
	case '*':return 4;break;
	case '/':return 4;break;
	case '%':return 4;break;
	case '^':return 6;break;
	case '(':return 8;break;
	case ')':return 1;break;
	case '=':return 0;break;
	}
}
string postfix() {//����׺���ʽתΪ��׺���ʽ
	Stack<char> s;
	string ans;
	string temp,ch;
	char  ch1,op;
	s.push('=');//��ջ�׷�'='
	cin >> temp;
	temp= '!' + temp;
	ch = '!'+temp;
	//����λ��Ϊ��Ŀ�����������
	for (int i = 2;s.empty() == false;) {
		if (isdigit(ch[i])) {
			ans += ch[i];
			i++;
		}
		else if ((ch[i] == '-' || ch[i] == '+' )&& isdigit(ch[i - 1]) == false&&ch[i-1]!=')') {//����Ŀ�����
			string temp2(ch,i+2);//������/�������������ʽ��
			ch[i - 2] = '(';
			ch[i - 1] = '0';
			ch[i + 2] = ')';
			ch.resize(i + 3);//����Ŀ�������Ϊ��(0+_?)"����ʽ
			ch = ch + temp2;
			i = i - 2;
		}
		else {
			ch1 = s.top();
			if (isp(ch1) < icp(ch[i]))//����������������ȼ���������ջ
			{
				s.push(ch[i]);
				i++;
			}
			else if (isp(ch1) > icp(ch[i]))//�����С����ջ����������
			{
				ans += s.top();
				s.pop();
			}
			else//����ȣ�����ջ�����
			{
				op = s.top();
				s.pop();
				if (op == '(')//��Ϊ'('�������һ�ַ�
					i++;
			}
		}
	}
	ans += '=';
	while (!s.empty())
		s.pop();
	return ans;
}

bool get(Stack<double>&num,double& left, double& right) {//�Ӳ�����ջ��ȡ������������
	if (num.empty() == true) {
		cerr << "ȱ���Ҳ�������" << endl;
		return false;
	}
	right = num.top();
	num.pop();
	if (num.empty() == true) {
		cerr << "ȱ�����������" << endl;
		return false;
	}
	left = num.top();
	num.pop();
	return true;
}
void Doperator(Stack<double>&num,char op)//�������
{
	double left, right, value;
	bool wrong;
	wrong = get(num,left, right);
	if (wrong == true)
		switch (op)
		{
		case '+':value = left + right;num.push(value);break;
		case '-':value = left - right;num.push(value);break;
		case '*':value = left * right;num.push(value);break;
		case '/':
			if (right == 0.0) {
			cerr << "����Ϊ0��" << endl;
			while (!num.empty())
				num.pop();
			exit(1);
		}
			else
		{
			value = left / right;num.push(value);
		}
			;break;
		case '%':value = (int)left % (int)right;num.push(value);break;
		case '^':value = pow(left, right);num.push(value);break;
		}
	else
	{
		while (!num.empty())
			num.pop();
		exit(1);
	}
}


