#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>        
#include <cstdlib>  
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <pthread.h>

#include "Character.h"		//字符元素类
#include "Menu.h"			//菜单界面类
#include "Matrix.h"			//面板(矩阵)类
#include "Record.h"			//历史纪录类

//#pragma comment(lib, "pthreadVC2.lib")

using namespace std;

HANDLE hout;

int matrix_size = 0;		//虚的矩阵大小 真正的矩阵(游戏面板边长大小)边长大小需要加上2
int mytime = 0;				//线程中开始计时变量			

//间接获取回车确定元素的坐标
int x = 1;
int y = 1;

//两次回车确定的游戏字符元素的坐标
int my_x1 = 1;
int my_y1 = 1;
int x2 = 1;
int y2 = 1;

int check_count = 0;		//回车确定的元素的数量
int success_count = 0;		//成功消除的累计变量，用来判断是否挑战成功


/*					连连看游戏的函数声明					*/	
int initialMeun();													//菜单的展示以及对难度的确定
void medium(vector<int>& data_medium, int& matrix_size);			//预处理数据，对数据的打乱作为，vector容器的媒介
char inputcontext(shared_ptr<Matrix>m, vector<Character>& matrix);	//实现通过键盘的上下左右实现光标的移动，以及回车键进行元素的确认
bool challenge(int matrix_size);									//判断游戏字符元素是否成功完全消除
void* countdown(void* arg);											//计时进程


int main() {

	srand(unsigned(time(0)));

	vector<Character> matrix;
	vector<int> data_medium;
	
	//菜单数据初始化
	matrix_size = initialMeun();
	
	char ch;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);

	//媒介数据
	medium(data_medium, matrix_size);

	//矩阵数据初始化及展开
	shared_ptr<Matrix> m(new Matrix(matrix_size + 2));
	m->initalMatrix(matrix_size + 2, data_medium, matrix);

	//创建开始计时的线程
	pthread_t tid;
	pthread_create(&tid, NULL, countdown, NULL);
	system("cls");
	
	//游戏的选择与消除
	while (1)
	{
		system("cls");	
		if (challenge(matrix_size))break;

	    m->showMatrix(matrix_size + 2, data_medium, matrix);
		ch = inputcontext(m, matrix);
		_putch(ch);	
	}
	
	cout << "您的挑战时间为:  " << mytime << "s" << endl;

	//对游戏时间进行判断，如若优于最佳历史记录则将本此游戏成绩载入文件
	Record(matrix_size).showInfo();
	return 0;
}


/*					连连看游戏的函数定义					*/

int initialMeun() {

	int choose = 0;
	int matrix_size = 4;

	Menu().print();
	cin >> choose;

	switch (Menu(choose).getChoose())
	{
	case 1:
		matrix_size = 4;
		break;
	case 2:
		matrix_size = 6;
		break;
	case 3:
		matrix_size = 8;
		break;
	}
	return matrix_size;
}

void medium(vector<int>& data_medium, int& matrix_size) {

	for (int i = 0; i < matrix_size * matrix_size; i++)
	{
		data_medium.push_back(i % matrix_size + 1);
	}
	random_shuffle(data_medium.begin(), data_medium.end());
}
 
char inputcontext(shared_ptr<Matrix>m, vector<Character>& matrix)
{
	int ch;
	COORD c;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	
	c.X = 3;
	c.Y = 9;

	printf("\033[%d;%dH", (3), (9));
	ch = _getch();
	//0x0d是回车的键码，0xe0是上下左右的键码

	while (ch == 0xe0 || ch == 0x0d)
	{

		GetConsoleScreenBufferInfo(hout, &csbi);
		c.X = csbi.dwCursorPosition.X;
		c.Y = csbi.dwCursorPosition.Y;
		//printf("\033[%d;%dH", (3), (9));
	
		if (ch == 0x0d)
		{
			check_count++;
			//printf("\033[%d;%dH", (13), (1));

			if (check_count == 1)
			{
				my_x1 = x;
				my_y1 = y;
				//x = 1;
				//y = 1;

			}
			else if (check_count == 2)
			{
				x2 = x;
				y2 = y;

				unsigned int i = 0;
				unsigned int j = 0;
				
				i = (matrix_size + 2) * my_y1 + my_x1;
				j = (matrix_size + 2) * y2 + x2;
				
				//for (i = 0; i < matrix.size() - 1; i++) {
				//	if (matrix[i].showX() == my_x1 && matrix[i].showY() == my_y1 && matrix[i].showData() != 0)
				//		break;
				//}
				//unsigned int j = 0;
				//for (j = 0; j < matrix.size() - 1; j++) {
				//	if (matrix[j].showX() == x2 && matrix[j].showY() == y2 && matrix[j].showData() != 0)
				//		break;
				//}

				if (matrix[i].showData() == matrix[j].showData() 
					&& (m->IsZeroTurnLinked(my_x1, my_y1, x2, y2, matrix) ||
						m->IsOneTurnLinked(my_x1, my_y1, x2, y2, matrix) ||
						m->IsTwoTurnLinked(my_x1, my_y1, x2, y2, matrix)
						)
					)
				{
					++success_count;
					matrix[i].setData(0);
					matrix[j].setData(0);
				}

				check_count = 0;
				x = 1;
				y = 1;
				my_x1 = 1;
				my_y1 = 1;
				x2 = 1;
				y2 = 1;
				break;
			}
		}
		else if (ch == 0xe0)
		{
			ch = _getch();
			if (ch == 0x48)//上
			{
				if (2 < c.Y) {
					c.Y--;
					y--;
				}
			}
			else if (ch == 0x50)//下
			{
				if (c.Y < 2 + m->getSize() - 3)
				{
					c.Y++;
					y++;
				}
			}
			else if (ch == 0x4b)//左
			{
				//if (c.X != 0)
				if (c.X > 9)
				{
					c.X -= 8;
					x--;

				}
			}
			else if (ch == 0x4d)//右
			{
				if (c.X < (m->getSize() - 2) * 8)//向右写79个字换行
				{
					c.X += 8;
					x++;
				}
			}
		}
		SetConsoleCursorPosition(hout, c);
		ch = _getch();
	}
	return ch;
}

bool challenge(int matrix_size) {
	if (matrix_size == 4 && success_count == 8)
	{
		cout << "挑战成功!" << endl;
		return true;
	}
	else if (matrix_size == 6 && success_count == 18)
	{
		cout << "挑战成功!" << endl;
		return true;
	}
	else if (matrix_size == 8 && success_count == 32)
	{
		cout << "挑战成功!" << endl;
		return true;
	}
	else
	{
		return false;
	}
}

void* countdown(void* arg) {

	while (++mytime)Sleep(1000);
	
	return NULL;
}