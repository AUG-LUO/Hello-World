//试定义一个类ID。实现一个成员函数extend，将15位的旧版身份证号扩充为18位。

//在15位身份证号中，第7、8两位为出生年份。例如，1980年出生的人，身份证号码的第7、8位是80；在18位身份证号中，将7 - 10四位的值改为1980，并将原身份证号码第9位开始以后的所有数字一次向右平移2位。在18位身份证号中，最后增加一位校验码，校验码的计算方法如下：

//将已扩展出的17位身份证号按各位上的数字进行加权求和，结果为S。自左到右各位上的数字的权值依次为：{ 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 }。
//将S对11取余运算，结果为Y。
//根据Y的取值大小顺序{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }取对应的校验码{ 1, 0, X, 9, 8, 7, 6, 5, 4, 3, 2 }。

#include <iostream>
using namespace std;
class ID
{
private:
	char new_id[19];
public:
	void extend(char* old_id)
	{
		int i, Y;
		for (i = 0;i < 6;i++)
			new_id[i] = old_id[i];
		new_id[6] = '1';
		new_id[7] = '9';
		for (i = 8;i < 17;i++)
			new_id[i] = old_id[i - 2];
		int num[17];
		for (i = 0;i < 17;i++)
			num[i] = new_id[i] - 48;
		Y = (num[0] * 7
			+ num[1] * 9
			+ num[2] * 10
			+ num[3] * 5
			+ num[4] * 8
			+ num[5] * 4
			+ num[6] * 2
			+ num[7] * 1
			+ num[8] * 6
			+ num[9] * 3
			+ num[10] * 7
			+ num[11] * 9
			+ num[12] * 10
			+ num[13] * 5
			+ num[14] * 8
			+ num[15] * 4
			+ num[16] * 2) % 11;
		if (Y >= 3 && Y <= 10)
			new_id[17] = '0' + 12 - Y;
		else if (Y == 0 || Y == 1)
			new_id[17] = '0' + 1 - Y;
		else
			new_id[17] = 'X';
		new_id[18] = 0;
	}
	void printf()
	{
		cout << new_id;
	}
};
int main()
{
	char old_id[16];
	cin >> old_id;
	ID id;
	id.extend(old_id);
	id.printf();
	return 0;
}