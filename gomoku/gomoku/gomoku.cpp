#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <unordered_map>
using namespace std;
#define ROW 10
#define COL 10
void Initial(vector<vector<char>>& board, int row, int col);
void View(vector<vector<char>> board, int row, int col);
int IsWin(vector<vector<char>> board, int row, int col);
void LdhMove(vector<vector<char>>&board, int row, int col);
void YouMove(vector<vector<char>>& board, int row, int col);


void Initial(vector<vector<char>>& board, int row, int col) 
{
	board.resize(row, vector<char>(col, ' '));
}

void View(vector<vector<char>> board, int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		cout<<"  " << i;
	}
	cout << endl;
	for (int i = 0; i < row; i++)
	{
		cout << i;
		for (int j = 0; j < col; j++)
		{
			cout << "|" << board[i][j] << "|";
		}
		cout << endl;
	}
}
class Ldh
{
public:
	int num;
	vector<pair<int, int>> p;
	Ldh() {};
	void Add(int x, int y)
	{
		p.push_back({ x, y });
	}
	//*
}L;
class You
{
public:
	vector<pair<int, int>> p;
	You() {};
	void Add(int x, int y)
	{
		p.push_back({ x,y });
	}
	//#
}Y;
void LdhMove(vector<vector<char>>& board, int row, int col)
{
LdhLife:
	cout << "Ldh please enter your coordinate using '*':>";
	int x = 0; 
	int y = 0;
	int flag = 1;
	cin >> x >> y;
	pair<int, int> me = { x,y };
	for (int i = 0; i < L.p.size(); i++)
	{
		if (me == L.p[i] || me == Y.p[i])
		{
			flag = 0;
		}
	}
	if (x >= 0 && x < row && y>=0 && y < row && flag)
	{
		board[x][y] = '*';

		L.Add(x, y);
	}
	else
	{
		cout << "please enter again" << endl;
		goto LdhLife;
	}
}
void YouMove(vector<vector<char>>& board, int row, int col)
{
YouLife:
	cout << "You please enter your coordinate using '*':>";
	int x = 0;
	int y = 0;
	int flag = 1;
	cin >> x >> y;
	pair<int, int> me = { x,y };
	for (int i = 0; i < Y.p.size(); i++)
	{
		if (me == Y.p[i] || me == L.p[i])
		{
			flag = 0;
		}
	}
	if (x >= 0 && x < row && y>=0 && y < row && flag)
	{
		board[x][y] = '#';

		Y.Add(x, y);
	}
	else
	{
		cout << "please enter again" << endl;
		goto YouLife;
	}
}
int IsWin(vector<vector<char>> board, int row, int col)
{
    char players[2] = { '*', '#' };
    for (int player = 0; player < 2; player++) {
        char symbol = players[player];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j <= col - 5; j++) {
                if (board[i][j] == symbol && board[i][j + 1] == symbol && 
                    board[i][j + 2] == symbol && board[i][j + 3] == symbol && 
                    board[i][j + 4] == symbol) {
                    return (symbol == '*') ? 1 : 2;
                }
            }
        }
        for (int j = 0; j < col; j++) {
            for (int i = 0; i <= row - 5; i++) {
                if (board[i][j] == symbol && board[i + 1][j] == symbol && 
                    board[i + 2][j] == symbol && board[i + 3][j] == symbol && 
                    board[i + 4][j] == symbol) {
                    return (symbol == '*') ? 1 : 2;
                }
            }
        }
        for (int i = 0; i <= row - 5; i++) {
            for (int j = 0; j <= col - 5; j++) {
                if (board[i][j] == symbol && board[i + 1][j + 1] == symbol &&
                    board[i + 2][j + 2] == symbol && board[i + 3][j + 3] == symbol &&
                    board[i + 4][j + 4] == symbol) {
                    return (symbol == '*') ? 1 : 2;
                }
            }
        }
        for (int i = 0; i <= row - 5; i++) {
            for (int j = 4; j < col; j++) {
                if (board[i][j] == symbol && board[i + 1][j - 1] == symbol &&
                    board[i + 2][j - 2] == symbol && board[i + 3][j - 3] == symbol &&
                    board[i + 4][j - 4] == symbol) {
                    return (symbol == '*') ? 1 : 2;
                }
            }
        }
    }

    return 0;  
}


void myenum()
{
	cout << "*********0.exit*********" << endl;
	cout << "*********1.enter*********" << endl;
}
int main()
{
	vector<vector<char>> board;
	int input = 0;
	do
	{
		myenum();
		cout << "enter you choice:>";
		cin >> input;
		switch (input)
		{
		case 0:
			break;
		case 1:
			Initial(board, ROW, COL);
			View(board, ROW, COL);

			while (!IsWin(board, ROW, COL))
			{
				LdhMove(board, ROW, COL);
				View(board, ROW, COL);
				if (IsWin(board, ROW, COL) == 1)
				{
					cout << "Ldh winer";
				}
				YouMove(board, ROW, COL);
				View(board, ROW, COL);
				if (IsWin(board, ROW, COL) == 2)
				{
					cout << "Ldh loser";
				}
			}
			break;
		default:
			cout << "please enter once again" << endl;
		}

	} while (input);


	return 0;
}


