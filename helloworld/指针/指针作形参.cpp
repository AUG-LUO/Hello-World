#include <iostream>
using namespace std;
int findmax(int p[][3], int m, int n, int* pRow, int* pCol)//��ָ�����βΣ���ַ��ʵ�Σ��ɸı�����ָ���ַ������
{
	int i, j;
	for (i = 0;i < m;i++)
		for (j = 0;j < n;j++)
			if (p[i][j] > p[*pRow][*pCol])
			{
				*pRow = i;
				*pCol = j;
			}
	return p[*pRow][*pCol];
}
int main()
{
	int i, j, a[2][3];
	for (i = 0;i < 2;i++)
		for (j = 0;j < 3;j++)
			cin >> a[i][j];
	int* pRow = new int;//��ʼ����ʱ������ռ�ͺ�
	int* pCol = new int;
	*pRow = 0;//�����ݵ�ֵ
	*pCol = 0;
	cout << findmax(a, 2, 3, pRow, pCol);
	cout << " " << *pRow << " " << *pCol;//���ܷŵ�һ���������Ϊ��ִ�������䣬��ִ�к�������
	return 0;
}