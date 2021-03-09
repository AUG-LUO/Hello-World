#ifndef HEAD_H
#define HEAD_H
using namespace std;
class Game
{
private:
	int chess[9][9];//9*9棋盘
	int point,num;//总得分&消除棋子数
	int change_r, change_c;//移动棋子坐标(0~8)
	bool reach;//判断到达
	int book[9][9];//标记数组
public:
	Game() :point(0), num(0), change_r(0), change_c(0) ,reach(false)
	{
		memset(chess, 0, sizeof(chess)); 
		memset(book, 0, sizeof(book));
	}//构造函数
	~Game() { }//析构函数
	void start();//游戏初始随机生成7子
	bool move(int old_r, int old_c, int new_r, int new_c);//移动棋子(1~9)
	void add();//随机生成3子
	void draw();//打印棋盘
	void print();//打印成绩

	bool jugde_empty();//判断空位
	bool jugde_kill_point();//判断+消除得分
	void jugde_kill();//判断+自动消除
	int jugde_end();//判断是否结束
	void jugde_way(int sr,int sc);//判断有效路径

};
#endif
