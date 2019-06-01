#include <iostream>
#include <Windows.h>
#include <graphics.h>   //ͼ�μ��ص�ͷ�ļ� 
#include <string>
#include <vector>
#include <functional>
#include <iterator>
#include <conio.h>  
#include <time.h>
#include <cstdlib> 
#include <mmsystem.h> //�������ֵ�ͷ�ļ�

#pragma comment(lib,"winmm.lib")  //  ���ֿ�

#define ENEMY_NUM 10  //�з�̹�˵����� �ú궨���Ա��ں��ڵ�ά�����޸�

using namespace std;

/**********************************************
*��ö�����г����������Ĭ�ϻ���Ϊint ��Ϊ�±�չʾ�Ƹ�
***********************************************/

enum DIRECTION    //  ����
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

/**************************************
*��ʼ��̹�˵Ľṹ��������࣬����Ч�ʻή��
***************************************/

struct Tank_init
{
	int x;          //������һ������
	int y;	        //������һ������
	DIRECTION direction;  //����
	bool live;	    //�Ƿ���   ���Ϊ true, �ҵ�Ϊ  false
};

/**************************************
*��ʼ���ӵ�
***************************************/

struct bullt_s
{
	int pos_x;
	int pos_y;
	DIRECTION pos_direcation;
	bool pos_state;
};

/**************************************
*��ʼ����Ϸ��ͼ
***************************************/

int map[26][26] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1},
	{2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,0,0,0,2,2,2,2,2,2,0,0,0,1,1,0,0,1,1,0,0},
	{0,0,1,1,0,0,0,0,0,2,2,2,2,2,2,0,0,0,1,1,0,0,1,1,0,0},
	{0,0,0,0,0,0,0,0,0,2,2,3,3,2,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,2,2,3,3,2,2,0,0,0,0,0,0,0,0,0,0,0}
};

/**************************************
*��������
***************************************/

void set_interface();//��ʼ����Ϸ��ͼ
void set_x_y_number(int x, int y, int flag);//���� x,y�����ֵ
void map_load(int *argv, int lenth, int width);//��ʼ����Ϸ��ͼ
void tank_move_control(Tank_init &my_tank, DIRECTION direction, IMAGE *image, int flag);//����̹�˵ķ���
void bullt_move(bullt_s & bullt);  //�����ӵ����˶��Լ��ӵ�����ײ���
void myenemy_tank_move_control(Tank_init &enemy_tank, DIRECTION direction, IMAGE *image);//�з����ҷ�̹�˵��˶�����
DIRECTION control_enemy_direction(Tank_init &tank, int x, int y);
void play();//ʵ����Ϸ����,����Tank����Ϸ���棨 �� ��

/**************************************
*�û��ӿ�
***************************************/

int main(void)
{
	/*
	string str;
	while (1)
	{
		cout << "��������";
		cin >> str;
		if (str == "��������˧")
		{
			system("cls");
			cout << "ôô�գ�" << endl;
			Sleep(2000);
			break;
		}
		else
		{
			system("cls");
			cout << "�����������ǲ�̫����Ӵ��" << endl;
			Sleep(2000);
			system("cls");
		}
	}
	system("cls");
	*/
	//���ڲ�����һ���ò��˺���ָ�� ����ߴ���Ŀ�ά���ԺͿɶ���  typedef void (*test)()
	initgraph(780, 760);
	mciSendString(_T("play 1.mp3 repeat"), 0, 0, 0);
	set_interface();
	map_load(&map[0][0], 26, 26);
	play();    
	system("pause");
	return 0;
}

/**************************************
*��ʼ����Ϸ��¼����
***************************************/

void set_interface()
{
	IMAGE logo_tank;
	loadimage(&logo_tank, _T("logo.bmp"), 0, 0, false);
	putimage(250, 20, &logo_tank);
	setlinecolor(RGB(255, 255, 255));
	rectangle(300, 190, 400, 250);
	rectangle(500, 190, 600, 250);
	settextcolor(RGB(255, 255, 0));
	settextstyle(50, 0, _T("΢���ź�"));
	outtextxy(310, 195, _T("˵��"));
	outtextxy(510, 195, _T("��ʼ"));
	IMAGE explain;
	loadimage(&explain, _T("˵��.jpg"), 300, 300);
	setfillcolor(BLACK);
	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg(); //��ȡ���״̬�ĺ���
		switch (mouse.uMsg)   //����״̬
		{
		case WM_MOUSEMOVE:
			if ((mouse.x > 300 && mouse.x < 400) && (mouse.y < 250 && mouse.y > 190))
			{
				putimage(220, 470, &explain);
			}
			else
			{
				solidrectangle(219, 469, 521, 771);
			}
			break;
		case WM_LBUTTONDOWN:
			if ((mouse.x > 500 && mouse.x < 600) && (mouse.y < 250 && mouse.y > 190))
			{
				cleardevice();  //�����Ա���ص�ͼ
				return;
			}
		}
	}
}

/**************************************
*���� x,y�����ֵ
***************************************/

void set_x_y_number(int x, int y, int flag)
{
	map[y][x] = flag;
	map[y + 1][x] = flag;
	map[y][x + 1] = flag;
	map[y + 1][x + 1] = flag;
}

/**************************************
*��ʼ����Ϸ��ͼ
***************************************/

void map_load(int *argv, int lenth, int width)//  �� y����  x
{                          //��        //��
	IMAGE wall_1, wall_2, home;
	loadimage(&wall_1, _T("wall1.jpg"), 30, 30);  //�ֻ�Ĥ
	loadimage(&wall_2, _T("wall2.jpg"), 30, 30);  //��ͨǽ
	loadimage(&home, _T("home.jpg"), 60, 60);  //С��
	for (int i = 0;i < width;i++)   //  y ��
	{
		for (int j = 0;j < lenth;j++)  // x  ��
		{
			if (*(argv + i * lenth + j) == 1)
			{
				putimage(30 * j, 30 * i, &wall_2);
			}
			else if (*(argv + i * lenth + j) == 2)
			{
				putimage(30 * j, 30 * i, &wall_1);
			}
			else if (*(argv + i * lenth + j) == 3)
			{
				putimage(30 * j, 30 * i, &home);
				*(argv + i * lenth + j) = 4;
				*(argv + i * lenth + j + 1) = 4;
				*(argv + (i + 1) * lenth + j) = 4;
				*(argv + (i + 1) * lenth + j + 1) = 4;
			}
		}
	}
}

/**************************************
*�����ӵ����˶��Լ��ӵ�����ײ���
***************************************/
void bullt_move(bullt_s & bullt)
{
	setfillcolor(BLACK);
	solidrectangle(bullt.pos_x, bullt.pos_y, bullt.pos_x + 3, bullt.pos_y + 3);
	int x1, y1, x, y;
	x = bullt.pos_x / 30;
	y = bullt.pos_y / 30;

	char bullt_musi[128];  // �洢�ļ���
	sprintf_s(bullt_musi, "E:\\vs��Ŀ\\tank_2\\tank_2\\boom.wav");

	if (bullt.pos_direcation == UP)
	{
		bullt.pos_y -= 2;
		y1 = y;
		x1 = x + 1;
	}
	else if (bullt.pos_direcation == DOWN)
	{
		bullt.pos_y += 2;
		y1 = y;
		x1 = x + 1;
	}
	else if (bullt.pos_direcation == LEFT)
	{
		bullt.pos_x -= 2;
		y1 = y + 1;
		x1 = x;
	}
	else if (bullt.pos_direcation == RIGHT)
	{
		bullt.pos_x += 2;
		y1 = y + 1;
		x1 = x;
	}
	else return;

	if (map[y1][x1] == 4 && map[y][x] == 4) 
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);   //�첽���ţ����Ч�ʲ�Ȼ��Ϸ�Ῠ�ġ�
	    return;
	}

	if (map[y1][x1] == 1)
	{
		PlaySound(bullt_musi, NULL , SND_ASYNC);   //�첽���ţ����Ч�ʲ�Ȼ��Ϸ�Ῠ�ġ�
		map[y1][x1] = 0;
		bullt.pos_state = false;
		setfillcolor(BLACK);
		solidrectangle(x1 * 30, y1 * 30, x1 * 30 + 30, y1 * 30 + 30);
	}
	else if (map[y1][x1] == 2)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//�첽���ţ����Ч�ʲ�Ȼ��Ϸ�Ῠ�ġ�
		bullt.pos_state = false;
	}
	if (map[y][x] == 1)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//�첽���ţ����Ч�ʲ�Ȼ��Ϸ�Ῠ�ġ�
		map[y][x] = 0;
		bullt.pos_state = false;
		setfillcolor(BLACK);
		solidrectangle(x * 30, y * 30, x * 30 + 30, y * 30 + 30);
	}
	else if (map[y][x] == 2)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//�첽���ţ����Ч�ʲ�Ȼ��Ϸ�Ῠ�ġ�
		bullt.pos_state = false;
	}

	if (bullt.pos_x < -3 || bullt.pos_x > 780 || bullt.pos_y < -3 || bullt.pos_y > 760)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//�첽���ţ����Ч�ʲ�Ȼ��Ϸ�Ῠ�ġ�
		bullt.pos_state = false;
	}
	if (bullt.pos_state == true)
	{
		setfillcolor(WHITE);
		solidrectangle(bullt.pos_x, bullt.pos_y, bullt.pos_x + 3, bullt.pos_y + 3);
	}
}

/**************************************
*����̹�˵ķ���
***************************************/

void tank_move_control(Tank_init &my_tank, DIRECTION direction, IMAGE *image, int flag)
{
	int new_x = my_tank.x; //��
	int new_y = my_tank.y; //��
	if (flag)
	{
		if (direction == UP)
		{
			new_y -= 1;
		}
		else if (direction == DOWN)
		{
			new_y += 1;
		}
		else if (direction == LEFT)
		{
			new_x -= 1;
		}
		else if (direction == RIGHT)
		{
			new_x += 1;
		}
		else return;
		set_x_y_number(my_tank.x, my_tank.y, 0);
	}
	setfillcolor(BLACK);
	solidrectangle(my_tank.x * 30, my_tank.y * 30, my_tank.x * 30 + 60, my_tank.y * 30 + 60);
	if (flag)  //���Ϊһ�ͰѸı��ֵ ��ֵ��ԭ����ֵ ����Ļ����ǵ�������
	{
		my_tank.x = new_x;
		my_tank.y = new_y;
		set_x_y_number(new_x, new_y, 200);
	}
	putimage(my_tank.x * 30, my_tank.y * 30, image);
	return;
}

/**************************************
 * �з����ҷ�̹�˵��˶�����
 **************************************/

void myenemy_tank_move_control(Tank_init &enemy_tank, DIRECTION direction, IMAGE *image)
{
	switch (direction) //�����˶��ķ��� ��������̹�˵ķ��򣬾���������̹�����Ǳ��ߣ�����������жϵ���̹�˵ķ����ƶ�
	{
	case UP:
		if (enemy_tank.direction == UP && (enemy_tank.y - 1) >= 0 && map[enemy_tank.y - 1][enemy_tank.x] == 0 && map[enemy_tank.y - 1][enemy_tank.x + 1] == 0)
		{
			tank_move_control(enemy_tank, UP, image, 1);
		}
		else if (enemy_tank.direction != UP)
		{
			enemy_tank.direction = UP;
			tank_move_control(enemy_tank, UP, image, 0);
		}
		break;
	case DOWN:
		if (enemy_tank.direction == DOWN && (enemy_tank.y + 2) <= 24 && map[enemy_tank.y + 2][enemy_tank.x] == 0 && map[enemy_tank.y + 2][enemy_tank.x + 1] == 0)
		{
			tank_move_control(enemy_tank, DOWN, image, 1);
		}
		else if (enemy_tank.direction != DOWN)
		{
			enemy_tank.direction = DOWN;
			tank_move_control(enemy_tank, DOWN, image, 0);
		}
		break;
	case LEFT:
		if (enemy_tank.direction == LEFT && (enemy_tank.x - 1) >= 0 && map[enemy_tank.y][enemy_tank.x - 1] == 0 && map[enemy_tank.y + 1][enemy_tank.x - 1] == 0)
		{
			tank_move_control(enemy_tank, LEFT, image, 1);
		}
		else if (enemy_tank.direction != LEFT)
		{
			enemy_tank.direction = LEFT;
			tank_move_control(enemy_tank, LEFT, image, 0);
		}
		break;
	case RIGHT:
		if (enemy_tank.direction == RIGHT && (enemy_tank.x + 2) <= 25 && map[enemy_tank.y][enemy_tank.x + 2] == 0 && map[enemy_tank.y + 1][enemy_tank.x + 2] == 0)
		{
			tank_move_control(enemy_tank, RIGHT, image, 1);
		}
		else if (enemy_tank.direction != RIGHT)
		{
			enemy_tank.direction = RIGHT;
			tank_move_control(enemy_tank, RIGHT, image, 0);
		}
		break;
	}
}

/**************************************
* �з�̹�˵�·���㷨 �����ҷ�̹�˺���ӥ
**************************************/
DIRECTION control_enemy_direction(Tank_init &tank, int x, int y)  //������������ѰĿ�� ����̹���Զ�Ѱ��Ŀ��
{
	int falg = rand() % 100;
	if (tank.x > x)
	{	
		if (tank.y > y)
		{
			if(falg <= 50)return UP;
			else return LEFT;
		}
		else
		{
			if (falg <= 50)return DOWN;
			else return LEFT;
		}
	}
	else
	{
		if (tank.y > y)
		{
			if (falg <= 50)return UP;
			else return RIGHT;
		}
		else
		{
			if (falg <= 50)return DOWN;
			else return RIGHT;
		}
	}
}

/**************************************
 *ʵ����Ϸ����   ����Tank����Ϸ���棨 �� ��
 **************************************/

void play()
{
	//�ҵ�̹�˺��ӵ�
	Tank_init my_tank;
	bullt_s my_bullt;

	//�з�̹�˺��ӵ�
	Tank_init enemy_tank[ENEMY_NUM];
	bullt_s enemy_tank_bullt[ENEMY_NUM];

	int enemy_total = 0; //��ǰ̹�˵����� 
	int times = 0; //�ƶ���ʱ����  �����ʱ�俪ʼ̹�˿�ʼ�ƶ�

	//�ҵ�̹�˵ĳ�ʼ��
	my_tank.x = 6;     //��
	my_tank.y = 23;   //�� 
	my_tank.live = true;
	my_bullt.pos_state = false; //�ӵ�������
	my_tank.direction = UP;
	set_x_y_number(my_tank.x, my_tank.y, 200);
	//��ʼ���з�̹�˵�״̬
	for (int i = 0;i < ENEMY_NUM; i++)
	{
		if (i % 3 == 0)enemy_tank[i].x = 0;
		else if (i % 3 == 1)enemy_tank[i].x = 12;
		else enemy_tank[i].x = 24;
		enemy_tank[i].y = 0;
		enemy_tank[i].live = true;
		enemy_tank[i].direction = DOWN;
		set_x_y_number(enemy_tank[i].x, enemy_tank[i].y, 100 + i); //�Ա��ڷֹ�
		enemy_tank_bullt[i].pos_state = false; // �з�̹���ӵ��ĳ�ʼ��
	}

	IMAGE my_tank_direcation_image[4];    //�ҷ�̹��ͼƬ����
	IMAGE enemy_tank_direcation_image[4]; //�з�̹�˵�ͼƬ����
	//�ҷ�̹��ͼƬ��ʼ��
	loadimage(&my_tank_direcation_image[UP], _T("tank_up.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[DOWN], _T("tank_down.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[LEFT], _T("tank_left.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[RIGHT], _T("tank_right.jpg"), 60, 60);
	//�з�̹��ͼƬ��ʼ��
	loadimage(&enemy_tank_direcation_image[UP], _T("enemy_tank_up.jpg"), 60, 60);
	loadimage(&enemy_tank_direcation_image[DOWN], _T("enemy_tank_down.jpg"), 60, 60);
	loadimage(&enemy_tank_direcation_image[LEFT], _T("enemy_tank_left.jpg"), 60, 60);
	loadimage(&enemy_tank_direcation_image[RIGHT], _T("enemy_tank_right.jpg"), 60, 60);
	//�����ҷ�̹��
	putimage(my_tank.x * 30, my_tank.y * 30, &my_tank_direcation_image[UP]);

	/*
	putimage(enemy_tank[0].x * 30, enemy_tank[0].y * 30, &enemy_tank_direcation_image[DOWN]);
	putimage(enemy_tank[1].x * 30, enemy_tank[1].y * 30, &enemy_tank_direcation_image[DOWN]);
	putimage(enemy_tank[2].x * 30, enemy_tank[2].y * 30, &enemy_tank_direcation_image[DOWN]);
	 */

	 //�з�̹�˳�ʼ��ͼƬ
	tank_move_control(enemy_tank[0], DOWN, &enemy_tank_direcation_image[DOWN], 0);
	tank_move_control(enemy_tank[1], DOWN, &enemy_tank_direcation_image[DOWN], 0);
	tank_move_control(enemy_tank[2], DOWN, &enemy_tank_direcation_image[DOWN], 0);
	enemy_total = 3;   //��ǰ̹������

	int key;    //��õ�ǰ���̵�����״̬
	srand((unsigned)time(NULL));
	while (true)
	{	
		if (times % 300 == 0)   //��ʱ�����з�̹�˵ķ���
		{
			for (int i = 0;i < enemy_total; i++)
			{
				if (i % 2 == 0)
				{
					DIRECTION d = control_enemy_direction(enemy_tank[i], 12, 24);
					myenemy_tank_move_control(enemy_tank[i], d, &enemy_tank_direcation_image[d]);
				}
				else
				{
					DIRECTION d = control_enemy_direction(enemy_tank[i], my_tank.x, my_tank.y);
					myenemy_tank_move_control(enemy_tank[i], d, &enemy_tank_direcation_image[d]);
				}
			}
		}
		else if (times % 50 == 0)   //̹��ÿ�� 1s �ƶ�һ��
		{
			for (int i = 0;i < enemy_total; i++)
			{
				if (enemy_tank[i].live)
				{
					DIRECTION d = control_enemy_direction(enemy_tank[i], my_tank.x, my_tank.y);
					myenemy_tank_move_control(enemy_tank[i], d, &enemy_tank_direcation_image[d]);
				}
			}
		}
		if (_kbhit())   //��������״̬������ֵ
		{
			key = _getch();   //��ȡ��ǰ״̬   �κ����������  λ�� #include <conio.h>��
			switch (key)
			{
			case 'w':    //��
				myenemy_tank_move_control(my_tank, UP, &my_tank_direcation_image[UP]); //����̹�˵��ƶ�
				break;
			case 's':    //��
				myenemy_tank_move_control(my_tank, DOWN, &my_tank_direcation_image[DOWN]);//����̹�˵��ƶ�
				break;
			case 'a':    //��
				myenemy_tank_move_control(my_tank, LEFT, &my_tank_direcation_image[LEFT]);//����̹�˵��ƶ�
				break;
			case 'd':    //��
				myenemy_tank_move_control(my_tank, RIGHT, &my_tank_direcation_image[RIGHT]);//����̹�˵��ƶ�
				break;
			case 'j':
				if (my_bullt.pos_state == false)   // �ӵ� ÿ��ֻ�ܷ�һ��
				{
					if (my_tank.direction == UP)
					{
						my_bullt.pos_x = my_tank.x * 30 + 27;
						my_bullt.pos_y = my_tank.y * 30 - 3;
					}
					else if (my_tank.direction == DOWN)
					{
						my_bullt.pos_x = my_tank.x * 30 + 27;
						my_bullt.pos_y = my_tank.y * 30 + 63;
					}
					else if (my_tank.direction == LEFT)
					{
						my_bullt.pos_x = my_tank.x * 30 - 3;
						my_bullt.pos_y = my_tank.y * 30 + 27;
					}
					else if (my_tank.direction == RIGHT)
					{
						my_bullt.pos_x = my_tank.x * 30 + 63;
						my_bullt.pos_y = my_tank.y * 30 + 27;
					}
					my_bullt.pos_direcation = my_tank.direction;
					my_bullt.pos_state = true;
				}
				break;
			case 'p':
				system("pause");   //��Ϸ��ͣ�� �����������
				break;
			default:     //����������Ч
				break;
			}
		}
		if (my_bullt.pos_state == true) bullt_move(my_bullt);  //����ӵ�����  �ƶ�
		Sleep(10);  //ÿ�����ߵ�ʱ��  �ܶ�  ��ֹ������  ���ع���  ��õ��Է���ûһ���ת��������
		times++;
	}
}
