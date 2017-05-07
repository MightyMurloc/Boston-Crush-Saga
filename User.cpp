#include "User.h"

bool loadUser(char *fName, user &usr)
{
	// Loads data of user from file 'userInfo.dat'. Returns true if loaded successfully.
	ifstream inFile(fName);
	if (inFile) {
		string	line;
		int		id = 0;
		while (getline(inFile, line)) {
			if (line[line.length() - 1] == '\r')
				line.erase(line.length() - 1);
			if (line.length() > 0) {
				istringstream iss(line);
				if (id == 0) {
					string name;
					iss >> name;
					usr.setName(name);
				}
			}
			id++;
		}
	}
	else {
		cout << "File not found!\n";
	}
	return true;
}

user::user() {
	this->score = 0; 
	this->name = "Average Joe";
}

string user::getName()
{
	return this->name;
}

void user::setName(string name) {
	this->name = name;
}

int user::getScore() {
	return this->score;
}

void user::setScore(int score) {
	this->score = score;
}
