#ifndef HEAD_H
#define HEAD_H
using namespace std;
void menu();//��ӡ�˵�����
class fraction
{
private:
	char* frac, *ans;//���롢����ַ���
	int numerator, denominator;//���ӣ���ĸ
public:
	fraction(char* f);
	//�����ַ����Ĺ��캯��
	void inverse();//ȡ�����㺯��
	void string_int() ;//ת��ֵ�ͷ������㺯��
	void reciprocal() ;//�������㺯��
	void reduction() ;//Լ�����㺯��
	void double_string() ;//С��ת�������㺯��
	void same_deno(fraction &c);//ͨ�ֺ���

	void operator *(fraction& c);
	void operator /(fraction& c);
	void operator +(fraction& c);
	void operator -(fraction& c);

	friend bool operator ==(fraction& c,fraction& c1);
	friend bool operator !=(fraction& c, fraction& c1);
	friend bool operator <(fraction& c,fraction& c1);
	friend bool operator >(fraction& c,fraction& c1);
	friend bool operator <=(fraction& c,fraction& c1);
	friend bool operator >=(fraction& c,fraction& c1);


	void show(int num) ;
	~fraction();
	
};

#endif