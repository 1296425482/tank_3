#include <iostream>
#include <Windows.h>
#include <graphics.h>   //图形加载的头文件 
#include <string>
#include <vector>
#include <functional>
#include <iterator>
#include <conio.h>  
#include <time.h>
#include <cstdlib> 
#include <mmsystem.h> //播放音乐的头文件

#pragma comment(lib,"winmm.lib")  //  音乐库

#define ENEMY_NUM 10  //敌方坦克的数量 用宏定义以便于后期的维护和修改

using namespace std;

/**********************************************
*用枚举来列出方向参数，默认基类为int 作为下标展示逼格
***********************************************/

enum DIRECTION    //  方向
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

/**************************************
*初始化坦克的结构体而不是类，用类效率会降低
***************************************/

struct Tank_init
{
	int x;          //所在那一列坐标
	int y;	        //所在那一行坐标
	DIRECTION direction;  //方向
	bool live;	    //是否存活   存活为 true, 挂掉为  false
};

/**************************************
*初始化子弹
***************************************/

struct bullt_s
{
	int pos_x;
	int pos_y;
	DIRECTION pos_direcation;
	bool pos_state;
};

/**************************************
*初始化游戏地图
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
*函数声明
***************************************/

void set_interface();//初始化游戏地图
void set_x_y_number(int x, int y, int flag);//设置 x,y坐标的值
void map_load(int *argv, int lenth, int width);//初始化游戏地图
void tank_move_control(Tank_init &my_tank, DIRECTION direction, IMAGE *image, int flag);//控制坦克的方向
void bullt_move(bullt_s & bullt);  //控制子弹的运动以及子弹的碰撞检测
void myenemy_tank_move_control(Tank_init &enemy_tank, DIRECTION direction, IMAGE *image);//敌方和我方坦克的运动控制
DIRECTION control_enemy_direction(Tank_init &tank, int x, int y);
void play();//实现游戏场景,就是Tank的游戏界面（ 玩 ）

/**************************************
*用户接口
***************************************/

int main(void)
{
	/*
	string str;
	while (1)
	{
		cout << "请输入口令：";
		cin >> str;
		if (str == "云翔哥儿最帅")
		{
			system("cls");
			cout << "么么哒！" << endl;
			Sleep(2000);
			break;
		}
		else
		{
			system("cls");
			cout << "看来，您还是不太懂我哟！" << endl;
			Sleep(2000);
			system("cls");
		}
	}
	system("cls");
	*/
	//由于参数不一样用不了函数指针 来提高代码的可维护性和可读性  typedef void (*test)()
	initgraph(780, 760);
	mciSendString(_T("play 1.mp3 repeat"), 0, 0, 0);
	set_interface();
	map_load(&map[0][0], 26, 26);
	play();    
	system("pause");
	return 0;
}

/**************************************
*初始化游戏登录界面
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
	settextstyle(50, 0, _T("微软雅黑"));
	outtextxy(310, 195, _T("说明"));
	outtextxy(510, 195, _T("开始"));
	IMAGE explain;
	loadimage(&explain, _T("说明.jpg"), 300, 300);
	setfillcolor(BLACK);
	MOUSEMSG mouse;
	while (true)
	{
		mouse = GetMouseMsg(); //获取鼠标状态的函数
		switch (mouse.uMsg)   //鼠标的状态
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
				cleardevice();  //清屏以便加载地图
				return;
			}
		}
	}
}

/**************************************
*设置 x,y坐标的值
***************************************/

void set_x_y_number(int x, int y, int flag)
{
	map[y][x] = flag;
	map[y + 1][x] = flag;
	map[y][x + 1] = flag;
	map[y + 1][x + 1] = flag;
}

/**************************************
*初始化游戏地图
***************************************/

void map_load(int *argv, int lenth, int width)//  行 y，列  x
{                          //行        //列
	IMAGE wall_1, wall_2, home;
	loadimage(&wall_1, _T("wall1.jpg"), 30, 30);  //钢化膜
	loadimage(&wall_2, _T("wall2.jpg"), 30, 30);  //普通墙
	loadimage(&home, _T("home.jpg"), 60, 60);  //小鸡
	for (int i = 0;i < width;i++)   //  y 行
	{
		for (int j = 0;j < lenth;j++)  // x  列
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
*控制子弹的运动以及子弹的碰撞检测
***************************************/
void bullt_move(bullt_s & bullt)
{
	setfillcolor(BLACK);
	solidrectangle(bullt.pos_x, bullt.pos_y, bullt.pos_x + 3, bullt.pos_y + 3);
	int x1, y1, x, y;
	x = bullt.pos_x / 30;
	y = bullt.pos_y / 30;

	char bullt_musi[128];  // 存储文件名
	sprintf_s(bullt_musi, "E:\\vs项目\\tank_2\\tank_2\\boom.wav");

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
		PlaySound(bullt_musi, NULL, SND_ASYNC);   //异步播放，提高效率不然游戏会卡的。
	    return;
	}

	if (map[y1][x1] == 1)
	{
		PlaySound(bullt_musi, NULL , SND_ASYNC);   //异步播放，提高效率不然游戏会卡的。
		map[y1][x1] = 0;
		bullt.pos_state = false;
		setfillcolor(BLACK);
		solidrectangle(x1 * 30, y1 * 30, x1 * 30 + 30, y1 * 30 + 30);
	}
	else if (map[y1][x1] == 2)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//异步播放，提高效率不然游戏会卡的。
		bullt.pos_state = false;
	}
	if (map[y][x] == 1)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//异步播放，提高效率不然游戏会卡的。
		map[y][x] = 0;
		bullt.pos_state = false;
		setfillcolor(BLACK);
		solidrectangle(x * 30, y * 30, x * 30 + 30, y * 30 + 30);
	}
	else if (map[y][x] == 2)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//异步播放，提高效率不然游戏会卡的。
		bullt.pos_state = false;
	}

	if (bullt.pos_x < -3 || bullt.pos_x > 780 || bullt.pos_y < -3 || bullt.pos_y > 760)
	{
		PlaySound(bullt_musi, NULL, SND_ASYNC);//异步播放，提高效率不然游戏会卡的。
		bullt.pos_state = false;
	}
	if (bullt.pos_state == true)
	{
		setfillcolor(WHITE);
		solidrectangle(bullt.pos_x, bullt.pos_y, bullt.pos_x + 3, bullt.pos_y + 3);
	}
}

/**************************************
*控制坦克的方向
***************************************/

void tank_move_control(Tank_init &my_tank, DIRECTION direction, IMAGE *image, int flag)
{
	int new_x = my_tank.x; //列
	int new_y = my_tank.y; //行
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
	if (flag)  //如果为一就把改变的值 赋值个原来的值 否则的话就是调整方向
	{
		my_tank.x = new_x;
		my_tank.y = new_y;
		set_x_y_number(new_x, new_y, 200);
	}
	putimage(my_tank.x * 30, my_tank.y * 30, image);
	return;
}

/**************************************
 * 敌方和我方坦克的运动控制
 **************************************/

void myenemy_tank_move_control(Tank_init &enemy_tank, DIRECTION direction, IMAGE *image)
{
	switch (direction) //即将运动的方向 ，而不是坦克的方向，就是你想让坦克往那边走，并用这个来判断调整坦克的方向移动
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
* 敌方坦克的路劲算法 来找我方坦克和老鹰
**************************************/
DIRECTION control_enemy_direction(Tank_init &tank, int x, int y)  //根据坐标来找寻目标 ，让坦克自动寻找目标
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
 *实现游戏场景   就是Tank的游戏界面（ 玩 ）
 **************************************/

void play()
{
	//我的坦克和子弹
	Tank_init my_tank;
	bullt_s my_bullt;

	//敌方坦克和子弹
	Tank_init enemy_tank[ENEMY_NUM];
	bullt_s enemy_tank_bullt[ENEMY_NUM];

	int enemy_total = 0; //当前坦克的数量 
	int times = 0; //移动的时间间隔  从这个时间开始坦克开始移动

	//我的坦克的初始化
	my_tank.x = 6;     //列
	my_tank.y = 23;   //行 
	my_tank.live = true;
	my_bullt.pos_state = false; //子弹不存在
	my_tank.direction = UP;
	set_x_y_number(my_tank.x, my_tank.y, 200);
	//初始化敌方坦克的状态
	for (int i = 0;i < ENEMY_NUM; i++)
	{
		if (i % 3 == 0)enemy_tank[i].x = 0;
		else if (i % 3 == 1)enemy_tank[i].x = 12;
		else enemy_tank[i].x = 24;
		enemy_tank[i].y = 0;
		enemy_tank[i].live = true;
		enemy_tank[i].direction = DOWN;
		set_x_y_number(enemy_tank[i].x, enemy_tank[i].y, 100 + i); //以便于分工
		enemy_tank_bullt[i].pos_state = false; // 敌方坦克子弹的初始化
	}

	IMAGE my_tank_direcation_image[4];    //我方坦克图片数组
	IMAGE enemy_tank_direcation_image[4]; //敌方坦克的图片数组
	//我方坦克图片初始化
	loadimage(&my_tank_direcation_image[UP], _T("tank_up.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[DOWN], _T("tank_down.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[LEFT], _T("tank_left.jpg"), 60, 60);
	loadimage(&my_tank_direcation_image[RIGHT], _T("tank_right.jpg"), 60, 60);
	//敌方坦克图片初始化
	loadimage(&enemy_tank_direcation_image[UP], _T("enemy_tank_up.jpg"), 60, 60);
	loadimage(&enemy_tank_direcation_image[DOWN], _T("enemy_tank_down.jpg"), 60, 60);
	loadimage(&enemy_tank_direcation_image[LEFT], _T("enemy_tank_left.jpg"), 60, 60);
	loadimage(&enemy_tank_direcation_image[RIGHT], _T("enemy_tank_right.jpg"), 60, 60);
	//加载我方坦克
	putimage(my_tank.x * 30, my_tank.y * 30, &my_tank_direcation_image[UP]);

	/*
	putimage(enemy_tank[0].x * 30, enemy_tank[0].y * 30, &enemy_tank_direcation_image[DOWN]);
	putimage(enemy_tank[1].x * 30, enemy_tank[1].y * 30, &enemy_tank_direcation_image[DOWN]);
	putimage(enemy_tank[2].x * 30, enemy_tank[2].y * 30, &enemy_tank_direcation_image[DOWN]);
	 */

	 //敌方坦克初始化图片
	tank_move_control(enemy_tank[0], DOWN, &enemy_tank_direcation_image[DOWN], 0);
	tank_move_control(enemy_tank[1], DOWN, &enemy_tank_direcation_image[DOWN], 0);
	tank_move_control(enemy_tank[2], DOWN, &enemy_tank_direcation_image[DOWN], 0);
	enemy_total = 3;   //当前坦克总数

	int key;    //获得当前键盘的输入状态
	srand((unsigned)time(NULL));
	while (true)
	{	
		if (times % 300 == 0)   //定时调整敌方坦克的方向
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
		else if (times % 50 == 0)   //坦克每隔 1s 移动一次
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
		if (_kbhit())   //键盘输入状态的所有值
		{
			key = _getch();   //获取当前状态   次函数不会回显  位于 #include <conio.h>中
			switch (key)
			{
			case 'w':    //上
				myenemy_tank_move_control(my_tank, UP, &my_tank_direcation_image[UP]); //控制坦克的移动
				break;
			case 's':    //下
				myenemy_tank_move_control(my_tank, DOWN, &my_tank_direcation_image[DOWN]);//控制坦克的移动
				break;
			case 'a':    //左
				myenemy_tank_move_control(my_tank, LEFT, &my_tank_direcation_image[LEFT]);//控制坦克的移动
				break;
			case 'd':    //右
				myenemy_tank_move_control(my_tank, RIGHT, &my_tank_direcation_image[RIGHT]);//控制坦克的移动
				break;
			case 'j':
				if (my_bullt.pos_state == false)   // 子弹 每次只能发一发
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
				system("pause");   //游戏暂停， 按任意键继续
				break;
			default:     //其他输入无效
				break;
			}
		}
		if (my_bullt.pos_state == true) bullt_move(my_bullt);  //如果子弹存活就  移动
		Sleep(10);  //每次休眠的时间  很短  防止处理器  负载过大  免得电脑风扇没一会就转的嗡嗡响
		times++;
	}
}
