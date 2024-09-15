#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
#define ROW 10
#define COL 10
void InitBoard(char** arr, int row, int col);
void ShowBoard(char arr[ROW][COL], int row, int col);
int IsWin(char arr[ROW][COL], int row, int col);
int MoveBoard(char arr[ROW][COL], int row, int col);
void FindY(char arr[ROW][COL], int row, int col);

void JudgeT(char arr[ROW][COL], int row, int col);
void FindT(char arr[ROW][COL], int row, int col);


struct YP
{
	int x;
	int y;
}yp;
struct TP 
{
	int x;
	int y;
}*tp;
struct TAC
{
	struct TP* t;
	int count;

}tac;




void menu()
{
	cout << "***********************" << endl;
	cout << "***********1.enter*****" << endl;
	cout << "***********0.exit******" << endl;
	cout << "***********************" << endl;
}
void intro()
{
	cout << "4 to left" << endl;
	cout << "2 to down" << endl;
	cout << "6 to right" << endl;
	cout << "8 to up" << endl;
	cout << "W represents wall" << endl;
	cout << "Y represents you" << endl;
	cout << "B represents box" << endl;
	cout << "T represents Targeted place" << endl;
}



void InitBoard(char** arr, int row, int col)
{

	strncpy(
		*arr,
		"\
|--------|\
|  | -   |\
|  |     |\
| Y| - - |\
| --     |\
| BT |   |\
|    |   |\
|  --    |\
|        |\
|--------|\n\
	", 100);
}
void FindY(char arr[ROW][COL],int row,int col)
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (arr[i][j] == 'Y')
			{
				yp.x = i;
				yp.y = j;

			}
		}
	}

	
}
void FindT(char arr[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	int count = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (arr[i][j] == 'T')
			{
				
				count++;
				struct TP* tmp = (struct TP*)realloc(tp, count * sizeof(struct TP));
				if (tmp == NULL)
				{
					perror("wrong realloc");
				}
				else 
				{
					tp = tmp;
					(tp+count-1)->x = i;
					(tp+count-1)->y = j;
					tac.t = tp;
					tac.count = count;
				}
			}
		}
	}
}

void ShowBoard(char arr[ROW][COL], int row, int col)
{
	cout << " ";
	for (int i = 0; i < col; i++)
	{
		cout << i;
	}
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		cout << i;
		for (int j = 0; j < col; j++)
		{
			cout << arr[i][j];
		}
		cout << endl;
	}
}
void Go(char arr[ROW][COL], int row, int col)
{
	int ret = 0;
	int count = 0;
	while (!ret)
	{
		ShowBoard(arr, ROW, COL);
		if (MoveBoard(arr, ROW, COL))
		{
			count++;
		}
		JudgeT(arr, ROW, COL);
		ret = IsWin(arr, ROW, COL);
	}
	cout << "step"<<count << endl;
	cout << "win!" << endl;
}
int IsWin(char arr[ROW][COL], int row, int col)
{
	int flag = 1;
	for (int i = 0; i < tac.count; i++)
	{
		if (arr[((tac.t) + i)->x][((tac.t) + i)->y] == 'T' || arr[((tac.t) + i)->x][((tac.t) + i)->y] == 'Y')
		{
			flag = 0;

		}
	}
	
	return flag;
}
void test()
{
	intro();
	char arr[ROW][COL];
	char* p = &arr[0][0];
	InitBoard(&p, ROW, COL);
	FindY(arr, ROW, COL);
	FindT(arr, ROW, COL);
	Go(arr,ROW,COL);
}
int MoveBoard(char arr[ROW][COL], int row,int col)
{
	int enter = 0;
	cout << "please move Y:>";
	cin >> enter;
	int flag = 1;
	if (enter == 4)
	{
		if (arr[(yp.x)][(yp.y) - 1] == '|' || arr[(yp.x)][(yp.y) - 1] == '-' 
			|| (arr[(yp.x)][yp.y - 1] == 'B' &&
				(arr[(yp.x)][(yp.y) - 2] == '|' || arr[(yp.x)][(yp.y) - 2] == '-' || arr[(yp.x)][(yp.y) - 2] == 'B')))
		{
			flag = 0;
		}
		else
		{
			if (arr[(yp.x)][yp.y - 1] == 'B')
			{
				arr[(yp.x)][yp.y - 2] = 'B';
			}
			arr[(yp.x)][yp.y - 1] = 'Y';
			arr[(yp.x)][yp.y] = ' ';
			
			yp.y -= 1;
			

		}
	}
	else if (enter == 6)
	{
		if (arr[(yp.x)][(yp.y) + 1] == '|' || arr[(yp.x)][(yp.y) + 1] == '-'
			|| (arr[(yp.x)][yp.y + 1] == 'B' &&
				(arr[(yp.x)][(yp.y) + 2] == '|' || arr[(yp.x)][(yp.y) + 2] == '-' || arr[(yp.x)][(yp.y) + 2] == 'B')))
		{
			flag = 0;
		}
		else
		{
			if (arr[(yp.x)][yp.y + 1] == 'B')
			{
				arr[(yp.x)][yp.y + 2] = 'B';

			}
			arr[(yp.x)][yp.y + 1] = 'Y';
			arr[(yp.x)][yp.y] = ' ';
			yp.y += 1;


		}
	}
	else if (enter == 2)
	{

		if (arr[(yp.x)+1][(yp.y) ] == '|' || arr[(yp.x)+1][(yp.y) ] == '-' 
			|| (arr[(yp.x)+1][yp.y ] == 'B' &&
				(arr[(yp.x)+2][(yp.y) ] == '|' || arr[(yp.x)+2][(yp.y) ] == '-' || arr[(yp.x) + 2][(yp.y)] == 'B')))
		{
			flag = 0;
		}
		else
		{
			if (arr[(yp.x) + 1][yp.y] == 'B')
			{
				arr[(yp.x) + 2][yp.y] = 'B';
			}
			arr[(yp.x) + 1][yp.y] = 'Y';
			arr[(yp.x)][yp.y] = ' ';
			yp.x += 1;

		}
	}
	else if (enter == 8)
	{

		if (arr[(yp.x) - 1][(yp.y)] == '|' || arr[(yp.x) - 1][(yp.y)] == '-' 
			|| (arr[(yp.x) - 1][yp.y] == 'B' &&
				(arr[(yp.x) - 2][(yp.y)] == '|' || arr[(yp.x) - 2][(yp.y)] == '-' || arr[(yp.x) - 2][(yp.y)] == 'B')))
		{
			flag = 0;
		}
		else
		{
			if (arr[(yp.x) - 1][yp.y] == 'B')
			{
				arr[(yp.x) - 2][yp.y] = 'B';
			}
			arr[(yp.x) - 1][yp.y] = 'Y';
			arr[(yp.x)][yp.y] = ' ';
			yp.x -= 1;

		}
	}
	else
	{
		flag = 0;
	}


	if (flag)
	{
		cout << "you move successfully" << endl;
		
	}
	else
	{
		cout << "invalid please enter again:>"<< endl;
	}
	return flag;
}
void JudgeT(char arr[ROW][COL], int row, int col)
{
	for (int i = 0; i < tac.count; i++)
	{
		if (arr[((struct TP*)(tac.t) + i)->x][((struct TP*)(tac.t) + i)->y] != 'Y' && 
			arr[((struct TP*)(tac.t) + i)->x][((struct TP*)(tac.t) + i)->y] != 'B')
		{
			arr[((struct TP*)(tac.t) + i)->x][((struct TP*)(tac.t) + i)->y] = 'T';
		}


	}



}

int main()
{
	int input = 0;
	
	do
	{
		menu();
		cout << "input your choice:>";
		cin >> input;
		switch (input)
		{
		case 1:
			test();
			break;
		case 0:
			cout << "exit successfully" << endl;
			break;
		default :
			cout << "please input a valid one" << endl;
		}
	} while (input);
	system("pause");
	return 0;
}