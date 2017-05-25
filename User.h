#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class user {
	string name;
	int score;
	int nMoves;
public:
	user();
	string getName();
	int getScore();
	int getMoves();
	void setName(string name);
	void setScore(int score);
	void setMoves(int nMoves);
	void importName(char *fName);
	void exportScore(char *fName, int score);
};