#include "User.h"
using namespace std;

user::user()
{
	this->name = "New player";
	this->score = 0;
	this->nMoves = 20;
}

string user::getName()
{
	return this->name;
}

int user::getScore()
{
	return this->score;
}

int user::getMoves()
{
	return this->nMoves;
}

void user::setName(string name)
{
	this->name = name;
}

void user::setScore(int score)
{
	this->score = score;
}

void user::setMoves(int nMoves)
{
	this->nMoves = nMoves;
}

void user::importName(char * fName)
{
	ifstream inFile(fName);
	if (inFile) {
		int id = 0;
		string line;
		while (getline(inFile, line)) {
			if (line[line.length() - 1] == '\r')
				line.erase(line.length() - 1);
			if (line.length() > 0) {
				if (id == 0) {
					string name = line.substr(6, line.length() - 1);
					this->name = name;
				}
				if (id == 1) {
					istringstream iss(line);
					string temp;
					iss >> temp >> this->nMoves;
				}
			}
			id++;
		}
	}
}

void user::exportScore(char * fName, int score)
{
	ofstream outFile;
	outFile.open(fName, ofstream::out | ofstream::app);
	if (outFile) {
		outFile << this->getName() << ": " << this->getScore() << endl;
	}
	outFile.close();
}
