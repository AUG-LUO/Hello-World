#include<iostream>
#include"Vector.h"
#include <cstring>
#include<cmath>
using namespace std;
int isp(char op);//栈内优先数
int icp(char op);//栈外优先数
string postfix();//将中缀表达式转为后缀表达式

bool get(Stack<double>& num, double& left, double& right); //从操作数栈中取出两个操作数
void Doperator(Stack<double>& num, char op);//运算操作

int main() {
	cout << "欢迎使用运算器！\n请输入您要计算的表达式（以=结尾）：" << endl;
	string s;
	Stack<double>operand;
	s=postfix();
	for (int i = 0; s[i] != '='; i++)
		if (isdigit(s[i]))
			operand.push((double)s[i] - (double)'0');
		else
			Doperator(operand, s[i]);
	cout << "运算结果为：" << operand.top()<<endl;
	while (!operand.empty())
		operand.pop();
	system("pause");
	return 0;
}
int isp(char op) {//栈内优先数
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
int icp(char op) {//栈外优先数
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
string postfix() {//将中缀表达式转为后缀表达式
	Stack<char> s;
	string ans;
	string temp,ch;
	char  ch1,op;
	s.push('=');//在栈底放'='
	cin >> temp;
	temp= '!' + temp;
	ch = '!'+temp;
	//留两位作为单目运算符缓冲区
	for (int i = 2;s.empty() == false;) {
		if (isdigit(ch[i])) {
			ans += ch[i];
			i++;
		}
		else if ((ch[i] == '-' || ch[i] == '+' )&& isdigit(ch[i - 1]) == false&&ch[i-1]!=')') {//处理单目运算符
			string temp2(ch,i+2);//拷贝正/负数后面的所有式子
			ch[i - 2] = '(';
			ch[i - 1] = '0';
			ch[i + 2] = ')';
			ch.resize(i + 3);//将单目运算符改为“(0+_?)"的形式
			ch = ch + temp2;
			i = i - 2;
		}
		else {
			ch1 = s.top();
			if (isp(ch1) < icp(ch[i]))//若后进入的运算符优先级大，则将其入栈
			{
				s.push(ch[i]);
				i++;
			}
			else if (isp(ch1) > icp(ch[i]))//若后进小，则将栈顶运算符输出
			{
				ans += s.top();
				s.pop();
			}
			else//若相等，则退栈不输出
			{
				op = s.top();
				s.pop();
				if (op == '(')//若为'('，则读下一字符
					i++;
			}
		}
	}
	ans += '=';
	while (!s.empty())
		s.pop();
	return ans;
}

bool get(Stack<double>&num,double& left, double& right) {//从操作数栈中取出两个操作数
	if (num.empty() == true) {
		cerr << "缺少右操作数！" << endl;
		return false;
	}
	right = num.top();
	num.pop();
	if (num.empty() == true) {
		cerr << "缺少左操作数！" << endl;
		return false;
	}
	left = num.top();
	num.pop();
	return true;
}
void Doperator(Stack<double>&num,char op)//运算操作
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
			cerr << "除数为0！" << endl;
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


