#include <iostream>
#include <Windows.h>
#include <graphics.h>
#include <string>
#include <vector>
#include <functional>
#include <iterator>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
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

void set_interface();
void set_x_y_number(int x, int y, int flag);
void map_load(int *argv, int lenth, int width);
void tank_move_control(Tank_init &my_tank, DIRECTION direction, IMAGE *image, int flag);
void bullt_move(bullt_s & bullt);
void play();

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
			if ( *(argv + i * lenth + j) == 1)
			{
				putimage(30 * j ,30 * i, &wall_2);
			}
			else if (*(argv + i * lenth + j) == 2)
			{
				putimage(30 * j , 30 * i, &wall_1);
			}
			else if (*(argv + i * lenth + j) == 3)
			{
				putimage( 30 * j, 30 * i, &home);
				*(argv + i * lenth + j) = 4;
				*(argv + i * lenth + j + 1) = 4;
				*(argv + (i + 1) * lenth + j ) = 4;
				*(argv + (i + 1) * lenth + j + 1 ) = 4;
			}
		}
	}
}

/**************************************
*�����ӵ��ķ���
***************************************/
void bullt_move(bullt_s & bullt)
{
	setfillcolor(BLACK);
	solidrectangle(bullt.pos_x , bullt.pos_y , bullt.pos_x + 3, bullt.pos_y + 3);
	if (bullt.pos_direcation == UP)
	{
		bullt.pos_y -= 2;
	}
	else if (bullt.pos_direcation == DOWN)
	{
		bullt.pos_y += 2;
	}
	else if (bullt.pos_direcation == LEFT)
	{
		bullt.pos_x -= 2;
	}
	else if (bullt.pos_direcation == RIGHT)
	{
		bullt.pos_x += 2;
	}
	else return;
	if (bullt.pos_x < -3 || bullt.pos_x > 780 || bullt.pos_y < -3 || bullt.pos_y > 760)
	{
		bullt.pos_state = false;
	}
	setfillcolor(WHITE);
	solidrectangle(bullt.pos_x , bullt.pos_y , bullt.pos_x + 3, bullt.pos_y + 3);
}

/**************************************
*����̹�˵ķ���
***************************************/

void tank_move_control(Tank_init &my_tank, DIRECTION direction, IMAGE *image, int flag)
{
	int new_x = my_tank.x; //��
	int new_y = my_tank.y; //��
	if (flag == 1)
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
		else return ;
		set_x_y_number(my_tank.x, my_tank.y, 0);
	}
	setfillcolor(BLACK);
	solidrectangle(my_tank.x * 30, my_tank.y * 30, my_tank.x * 30 + 60, my_tank.y * 30 + 60);
	if (flag)
	{
		my_tank.x = new_x; 
		my_tank.y = new_y;
		set_x_y_number(new_x, new_y, 200);
	}
	putimage(my_tank.x * 30, my_tank.y * 30, image);
	return ;
}

/**************************************
 *ʵ����Ϸ����   ����Tank����Ϸ����
 **************************************/

void play()
{
	Tank_init my_tank;
	bullt_s my_bullt;
	my_tank.x = 6;     //��
	my_tank.y = 23;   //�� 
	my_tank.live = true;
	my_bullt.pos_state = false ; //�ӵ�������
	my_tank.direction = UP;
	set_x_y_number(my_tank.x, my_tank.y, 200);
	IMAGE my_tank_direcation_image[4];
	loadimage(&my_tank_direcation_image[UP], _T("tank_up.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[DOWN], _T("tank_down.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[LEFT], _T("tank_left.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[RIGHT], _T("tank_right.jpg"), 60, 60);
	putimage(my_tank.x * 30, my_tank.y * 30, &my_tank_direcation_image[UP]);
	int key;
	while (true)
	{
		if (_kbhit())
		{
			key = _getch();
			switch (key)
			{
				case 'w':
					if (my_tank.direction == UP && (my_tank.y - 1) >= 0 && map[my_tank.y - 1][my_tank.x] == 0 && map[my_tank.y - 1][my_tank.x + 1] == 0)
					{
						tank_move_control(my_tank, UP, &my_tank_direcation_image[my_tank.direction], 1);
					}
					else if(my_tank.direction != UP)
					{
						my_tank.direction = UP;
						tank_move_control(my_tank, UP, &my_tank_direcation_image[my_tank.direction], 0);
					}
					break;
				case 's':
					if (my_tank.direction == DOWN && (my_tank.y + 2) <= 24 && map[my_tank.y + 2][my_tank.x] == 0 && map[my_tank.y + 2][my_tank.x + 1] == 0)
					{
						tank_move_control(my_tank, DOWN, &my_tank_direcation_image[my_tank.direction], 1);
					}
					else if(my_tank.direction != DOWN)
					{
						my_tank.direction = DOWN;
						tank_move_control(my_tank, DOWN, &my_tank_direcation_image[my_tank.direction], 0);
					}
					break;
				case 'a':
					if (my_tank.direction == LEFT && (my_tank.x - 1) >= 0 && map[my_tank.y ][my_tank.x - 1] == 0 && map[my_tank.y + 1][my_tank.x - 1] == 0)
					{
						tank_move_control(my_tank, LEFT, &my_tank_direcation_image[my_tank.direction], 1);					
					}
					else if(my_tank.direction != LEFT)
					{
						my_tank.direction = LEFT;
						tank_move_control(my_tank, LEFT, &my_tank_direcation_image[my_tank.direction], 0);			
					}
					break;
				case 'd':
					if (my_tank.direction == RIGHT && (my_tank.x + 2) <= 25 && map[my_tank.y][my_tank.x + 2] == 0 && map[my_tank.y + 1][my_tank.x + 2] == 0)
					{
						tank_move_control(my_tank, RIGHT, &my_tank_direcation_image[my_tank.direction], 1);
					}
					else if(my_tank.direction != RIGHT)
					{
						my_tank.direction = RIGHT;
						tank_move_control(my_tank, RIGHT, &my_tank_direcation_image[my_tank.direction], 0);					
					}
					break;
				case 'j':
					if (my_bullt.pos_state == false)
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
					system("pause");
					break;
				default:
					break;
			}
		}
		if(my_bullt.pos_state == true) bullt_move(my_bullt);
		Sleep(10);
	}
}
