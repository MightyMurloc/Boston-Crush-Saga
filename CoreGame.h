#pragma once
#include <ctime>
#include <algorithm>
#include <cmath>
#include <Windows.h>
#include "termcolor.hpp"
#include "user.h"

using namespace std;

typedef struct piece {
	int		col, row;
	int		kind;
	int		match;
public:
	piece();
	void setCoord(int, int);
} board[10][10];

void selectGem(string, int&, int&);
void swapGem(piece&, piece&, board&);
void boardInit(board&);
void drawBoard(board&);
void matchFinding(board&);
void gridUpdate(board&);