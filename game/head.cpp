#include<iostream>
#include"head.h"
#include<cstdlib>
#include<ctime>
using namespace std;


void Game::start()
{
	srand((unsigned)time(NULL));
	for (int i = 1;i <= 7;i++)
	{
		change_r = rand() % 9;
		change_c = rand() % 9;
		if (jugde_empty())
			chess[change_r][change_c] = i;
		else
			i--;
	}
}
bool Game::move(int old_r, int old_c,int new_r,int new_c)
{
	change_r = new_r-1;
	change_c = new_c-1;

	reach = false;
	memset(book, 0, sizeof(book));
	book[old_r - 1][old_c - 1] = 1;
	jugde_way(old_r - 1, old_c - 1);

	if (jugde_empty()
		&& reach
		&& chess[old_r - 1][old_c - 1]
		&& (old_r < 10 && old_r>0 && old_c < 10 && old_c>0)
		&& (new_r < 10 && new_r>0 && new_c < 10 && new_c>0))
	{
		chess[change_r][change_c] = chess[old_r - 1][old_c - 1];
		chess[old_r - 1][old_c - 1] = 0;
		draw();
		system("pause");
		return true;
	}
	else
	{
		cout << "�ƶ�ָ�������������ƶ�!" << endl;
		system("pause");
		return false;
	}
}
void Game::add()
{
	srand((unsigned)time(NULL));
	int temp = jugde_end();//������������
	int t[3][2] = { 0 };//������������
	for (int i = 0;i < temp;i++)
	{
		t[i][0] = rand() % 9;
		t[i][1] = rand() % 9;
		change_r = t[i][0];
		change_c = t[i][1];
		if (jugde_empty())
			chess[change_r][change_c] = rand() % 7 + 1;
		else
			i--;
	}
	draw();
	cout << "������" << endl;
	if (temp == 3)
	{
		for (int i = 0;i < 3;i++)
		{
			change_r = t[i][0];
			change_c = t[i][1];
			jugde_kill();
		}
		draw();
	}
}
void Game::draw()
{
	system("cls");
	cout << "<<<<<<<<<<<��������>>>>>>>>>>" << endl;
	cout << "   (1)(2)(3)(4)(5)(6)(7)(8)(9)" << endl;
	for (int i = 0;i < 9;i++)
	{
		cout << '(' << i+1 << ") ";
		for (int j = 0;j < 9;j++)
		{
			if (chess[i][j] == 0)
				cout << '*' << "  ";
			else
				cout << chess[i][j] << "  ";
		}
		cout << endl;
	}
}
void Game::print()
{
	point = num * 2;
	cout << "��Ϸ���������ĳɼ�Ϊ��" << point << endl;
}

bool Game::jugde_empty()
{
	if (chess[change_r][change_c] == 0)
		return true;
	return false;
}
bool Game::jugde_kill_point()
{
	int n=0, direction=0;//ÿ������������&��������
	int color = chess[change_r][change_c];//���жϵ���ɫ
	int up=change_r-1, down=change_r+1, left=change_c-1, right=change_c+1;//��¼������Χ
	for (;up >= 0;up--)//�����ж�
		if (chess[up][change_c] != color)
			break;
		else
			n++;
	for (;down< 9;down++)//�����ж�
		if (chess[down][change_c] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num =num+n+1;
		for (up++;n >= 0;up++, n--)//��������
			chess[up][change_c] = 0;
	}

	n = 0;
	for (;left >= 0;left--)//�����ж�
		if (chess[change_r][left] != color)
			break;
		else
			n++;
	for (;right < 9;right++)//�����ж�
		if (chess[change_r][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num = num + n + 1;
		for (left++;n >= 0;left++, n--)//��������
			chess[change_r][left] = 0;
	}

	n = 0;
	up = change_r - 1;down = change_r + 1;left = change_c - 1;right = change_c + 1;
	for (;up >= 0 && left >= 0;up--, left--)//�������ж�
		if (chess[up][left] != color)
			break;
		else
			n++;
	for (;down < 9 && right < 9 ;down++, right++)//�������ж�
		if (chess[down][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num = num + n + 1;
		for (up++,left++;n >= 0;up++,left++, n--)//��������
			chess[up][left] = 0;
	}

	n = 0;
	up = change_r-1;down = change_r+1;left = change_c-1;right = change_c+1;
	for (;up >= 0 && right < 9;up--, right++)//�������ж�
		if (chess[up][right] != color)
			break;
		else
			n++;
	for (;down < 9 && left >= 0;down++, left--)//�������ж�
		if (chess[down][left] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num = num + n + 1;
		for (up++, right--;n >= 0;up++, right--, n--)//��������
			chess[up][right] = 0;
	}

	if (direction > 0)
	{
		num = num + 1 - direction;
		draw();
		cout << "����ȥ" << num << "��" << endl;
		system("pause");
		return true;
	}
	cout << "����ȥ" << num << "��" << endl;
	system("pause");
	return false;
}
void Game::jugde_kill()
{
	int n = 0;//ÿ������������
	int color = chess[change_r][change_c];//���жϵ���ɫ
	int up = change_r - 1, down = change_r + 1, left = change_c - 1, right = change_c + 1;//��¼������Χ
	for (;up >= 0;up--)//�����ж�
		if (chess[up][change_c] != color)
			break;
		else
			n++;
	for (;down < 9 ;down++)//�����ж�
		if (chess[down][change_c] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (up++;n >= 0;up++, n--)//��������
			chess[up][change_c] = 0;
	}

	n = 0;
	for (;left >= 0;left--)//�����ж�
		if (chess[change_r][left] != color)
			break;
		else
			n++;
	for (;right < 9 ;right++)//�����ж�
		if (chess[change_r][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (left++;n >= 0;left++, n--)//��������
			chess[change_r][left] = 0;
	}

	n = 0;
	up = change_r - 1;down = change_r + 1;left = change_c - 1;right = change_c + 1;
	for (;up >= 0 && left >= 0;up--, left--)//�������ж�
		if (chess[up][left] != color)
			break;
		else
			n++;
	for (;down < 9 && right < 9;down++, right++)//�������ж�
		if (chess[down][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (up++, left++;n >= 0;up++, left++, n--)//��������
			chess[up][left] = 0;
	}

	n = 0;
	up = change_r - 1;down = change_r + 1;left = change_c - 1;right = change_c + 1;
	for (;up >= 0 && right < 9;up--, right++)//�������ж�
		if (chess[up][right] != color)
			break;
		else
			n++;
	for (;down < 9 && left >= 0 ;down++, left--)//�������ж�
		if (chess[down][left] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (up++, right--;n >= 0;up++, right--, n--)//��������
			chess[up][right] = 0;
	}
}
int Game::jugde_end()
{
	int n=0;//�ո���
	for (int i = 0;i < 9;i++)
		for (int j = 0;j < 9;j++)
		{
			if (chess[i][j] == 0)
				n++;
			if (n == 3)
				return 3;
		}
	return n;
}

void Game::jugde_way(int sr, int sc)
{
	int tr, tc, k;
	int next[4][2] = { {-1,0} ,{1,0},{0,-1}, {0,1} };//��������
	if (sr == change_r && sc == change_c)//�ж��Ƿ��ѵ���
	{
		reach = true;
		return;
	}
	if (!reach)
	{	for (k = 0;k < 4;k++)
		{
			tr = sr + next[k][0];
			tc = sc + next[k][1];
			if (tr < 0 || tr>8 || tc < 0 || tc>8)
				continue;
			if (chess[tr][tc] == 0 && book[tr][tc] == 0)
			{
				book[tr][tc] = 1;//������߹�
				jugde_way(tr, tc);//������һ����
				book[tr][tc] = 0;//���Խ���������
			}
		}
	}
	return ;
}
