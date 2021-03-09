#ifndef HEAD_H
#define HEAD_H
using namespace std;
class Game
{
private:
	int chess[9][9];//9*9����
	int point,num;//�ܵ÷�&����������
	int change_r, change_c;//�ƶ���������(0~8)
	bool reach;//�жϵ���
	int book[9][9];//�������
public:
	Game() :point(0), num(0), change_r(0), change_c(0) ,reach(false)
	{
		memset(chess, 0, sizeof(chess)); 
		memset(book, 0, sizeof(book));
	}//���캯��
	~Game() { }//��������
	void start();//��Ϸ��ʼ�������7��
	bool move(int old_r, int old_c, int new_r, int new_c);//�ƶ�����(1~9)
	void add();//�������3��
	void draw();//��ӡ����
	void print();//��ӡ�ɼ�

	bool jugde_empty();//�жϿ�λ
	bool jugde_kill_point();//�ж�+�����÷�
	void jugde_kill();//�ж�+�Զ�����
	int jugde_end();//�ж��Ƿ����
	void jugde_way(int sr,int sc);//�ж���Ч·��

};
#endif
