#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

typedef class user {
	string	name;
public:
	int		score;
	user();
	string getName();
	void setName(string);
	int getScore();
	void setScore(int);
};

bool loadUser(char*, user&);