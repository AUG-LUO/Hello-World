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
		cout << "移动指令有误，请重新移动!" << endl;
		system("pause");
		return false;
	}
}
void Game::add()
{
	srand((unsigned)time(NULL));
	int temp = jugde_end();//可生成棋子数
	int t[3][2] = { 0 };//生成棋子坐标
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
	cout << "已生成" << endl;
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
	cout << "<<<<<<<<<<<五子连珠>>>>>>>>>>" << endl;
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
	cout << "游戏结束，您的成绩为：" << point << endl;
}

bool Game::jugde_empty()
{
	if (chess[change_r][change_c] == 0)
		return true;
	return false;
}
bool Game::jugde_kill_point()
{
	int n=0, direction=0;//每次消除棋子数&消除方向
	int color = chess[change_r][change_c];//需判断的颜色
	int up=change_r-1, down=change_r+1, left=change_c-1, right=change_c+1;//记录消除范围
	for (;up >= 0;up--)//向上判断
		if (chess[up][change_c] != color)
			break;
		else
			n++;
	for (;down< 9;down++)//向下判断
		if (chess[down][change_c] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num =num+n+1;
		for (up++;n >= 0;up++, n--)//置零消除
			chess[up][change_c] = 0;
	}

	n = 0;
	for (;left >= 0;left--)//向左判断
		if (chess[change_r][left] != color)
			break;
		else
			n++;
	for (;right < 9;right++)//向右判断
		if (chess[change_r][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num = num + n + 1;
		for (left++;n >= 0;left++, n--)//置零消除
			chess[change_r][left] = 0;
	}

	n = 0;
	up = change_r - 1;down = change_r + 1;left = change_c - 1;right = change_c + 1;
	for (;up >= 0 && left >= 0;up--, left--)//向左上判断
		if (chess[up][left] != color)
			break;
		else
			n++;
	for (;down < 9 && right < 9 ;down++, right++)//向右下判断
		if (chess[down][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num = num + n + 1;
		for (up++,left++;n >= 0;up++,left++, n--)//置零消除
			chess[up][left] = 0;
	}

	n = 0;
	up = change_r-1;down = change_r+1;left = change_c-1;right = change_c+1;
	for (;up >= 0 && right < 9;up--, right++)//向右上判断
		if (chess[up][right] != color)
			break;
		else
			n++;
	for (;down < 9 && left >= 0;down++, left--)//向左下判断
		if (chess[down][left] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		direction++;
		num = num + n + 1;
		for (up++, right--;n >= 0;up++, right--, n--)//置零消除
			chess[up][right] = 0;
	}

	if (direction > 0)
	{
		num = num + 1 - direction;
		draw();
		cout << "已消去" << num << "子" << endl;
		system("pause");
		return true;
	}
	cout << "已消去" << num << "子" << endl;
	system("pause");
	return false;
}
void Game::jugde_kill()
{
	int n = 0;//每次消除棋子数
	int color = chess[change_r][change_c];//需判断的颜色
	int up = change_r - 1, down = change_r + 1, left = change_c - 1, right = change_c + 1;//记录消除范围
	for (;up >= 0;up--)//向上判断
		if (chess[up][change_c] != color)
			break;
		else
			n++;
	for (;down < 9 ;down++)//向下判断
		if (chess[down][change_c] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (up++;n >= 0;up++, n--)//置零消除
			chess[up][change_c] = 0;
	}

	n = 0;
	for (;left >= 0;left--)//向左判断
		if (chess[change_r][left] != color)
			break;
		else
			n++;
	for (;right < 9 ;right++)//向右判断
		if (chess[change_r][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (left++;n >= 0;left++, n--)//置零消除
			chess[change_r][left] = 0;
	}

	n = 0;
	up = change_r - 1;down = change_r + 1;left = change_c - 1;right = change_c + 1;
	for (;up >= 0 && left >= 0;up--, left--)//向左上判断
		if (chess[up][left] != color)
			break;
		else
			n++;
	for (;down < 9 && right < 9;down++, right++)//向右下判断
		if (chess[down][right] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (up++, left++;n >= 0;up++, left++, n--)//置零消除
			chess[up][left] = 0;
	}

	n = 0;
	up = change_r - 1;down = change_r + 1;left = change_c - 1;right = change_c + 1;
	for (;up >= 0 && right < 9;up--, right++)//向右上判断
		if (chess[up][right] != color)
			break;
		else
			n++;
	for (;down < 9 && left >= 0 ;down++, left--)//向左下判断
		if (chess[down][left] != color)
			break;
		else
			n++;
	if (n > 3)
	{
		for (up++, right--;n >= 0;up++, right--, n--)//置零消除
			chess[up][right] = 0;
	}
}
int Game::jugde_end()
{
	int n=0;//空格数
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
	int next[4][2] = { {-1,0} ,{1,0},{0,-1}, {0,1} };//上下左右
	if (sr == change_r && sc == change_c)//判断是否已到达
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
				book[tr][tc] = 1;//标记已走过
				jugde_way(tr, tc);//尝试下一个点
				book[tr][tc] = 0;//尝试结束，置零
			}
		}
	}
	return ;
}
