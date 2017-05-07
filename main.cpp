#include <conio.h>
#include "User.h"
#include "CoreGame.h"

using namespace std;

int main() {
	srand(time(NULL));
	user	user;
	board	grid;
	int		choice;

	system("COLOR 02");
	cout << "Welcome to Boston Crush Saga!\n"
		 << "PF162A01 - Spring 2017\n"
		 << "__________________________\n";
	cout << "-------- Main Menu -------\n"
		 << "1. New game\n"
		 << "2. Instruction\n"
		 << "3. Hi-score\n"
		 << "4. Exit\n"
		 << "Enter your choice: ";
	cin >> choice;
	if (choice == 1) {
		int score = 0;
		boardInit(grid);
		while (score <= 10000) { //Any suggestions? The game will exit when score is 10000, or user quit early.
			int sum = 0;
			matchFinding(grid);
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					sum += grid[i][j].match;
			while (sum > 0) {
				gridUpdate(grid);
				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 10; j++)
						grid[i][j].match = 0;
				matchFinding(grid);
				sum = 0;
				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 10; j++)
						sum += grid[i][j].match;
			}
			drawBoard(grid);
			cout << "Score: " << user.getScore() << endl;
			int row_1, row_2, col_1, col_2;
			selectGem("gem 1", row_1, col_1);
			selectGem("gem 2", row_2, col_2);
			while (fabs(row_1 - row_2) != 1 && fabs(col_1 - col_2) != 1) { // User can only swap adjecent gems.
				drawBoard(grid);
				cout << "Score: " << score << endl;
				cout << "Invalid move!\n";
				selectGem("gem 1", row_1, col_1);
				selectGem("gem 2", row_2, col_2);
			}
			swap(grid[row_1][col_1].kind, grid[row_2][col_2].kind);
			for (int i = 1; i <= 10; ++i)
				for (int j = 1; j <= 10; ++j)
					grid[i][j].match = 0;
			matchFinding(grid);
			sum = 0;
			for (int i = 0; i < 10; i++)
				for (int j = 0; j < 10; j++)
					sum += grid[i][j].match;
			while (sum == 0) { // User can only swap gems so that it creates a match.
				swap(grid[row_1][col_1].kind, grid[row_2][col_2].kind);
				drawBoard(grid);
				cout << "Score: " << score << endl;
				cout << "Invalid move!\n";
				selectGem("gem 1", row_1, col_1);
				selectGem("gem 2", row_2, col_2);
				sum = 0;
				for (int i = 0; i < 10; i++)
					for (int j = 0; j < 10; j++)
						sum += grid[i][j].match;
			}
			for (int i = 1; i <= 10; ++i)
				for (int j = 1; j <= 10; ++j)
					score += grid[i][j].match * 100;
			user.setScore(score); // Updates score.
		}
	}
	if (choice == 2); // Please create a function in CoreGame.h and CoreGame.cpp, and make it funny! (Pro tip: use system("cls") to clear screen).
	if (choice == 3); // Please create a function to output <user_name> - <score> on a file "Score.dat". Then read from it to display hi-score.
	if (choice == 4) return 0;
	// What if user input some shitty choices like "Allahu Akbar"?. Implement this too.
	return 0;
}