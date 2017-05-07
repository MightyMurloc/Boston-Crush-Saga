#include "CoreGame.h"
#include "user.h"

piece::piece() {
	this->match = 0;
	this->kind = rand() % 6 + 1; // Constructor.
}

void piece::setCoord(int row, int col) {
	this->row = row;
	this->col = col; // For use in selectGem()
}

void selectGem(string gem, int &row, int &col) {
	string temp;
	cout << "Enter " << gem << " row: ";
	cin >> row;
	cout << "Enter " << gem << " column: ";
	cin >> col;
}

void boardInit(board &grid) {
	srand(time(0)); // Seed for randomization
	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 10; ++j) {
			piece *p = new piece;
			grid[i][j] = *p;
			grid[i][j].setCoord(i, j);
		}
	}
}

void drawBoard(board &grid) {
	system("cls");
	system("color 08");
	printf("\n");
	printf("   0  1  2  3  4  5  6  7  8  9\n");
	for (int i = 0; i < 10; ++i) {
		printf("%d ", i);
		for (int j = 0; j < 10; ++j) {
			printf("[%d]", grid[i][j].kind);
		}
		printf("\n");
	}
	printf("\n");
}

void matchFinding(board &grid) {
	for (int i = 0; i <= 9; ++i) {
		for (int j = 0; j <= 9; ++j) {
			if (grid[i][j].kind == grid[i + 1][j].kind && grid[i][j].kind == grid[i - 1][j].kind) // Pretty straightfoward stuff.
				for (int c = -1; c <= 1; ++c) grid[i + c][j].match++;
			if (grid[i][j].kind == grid[i][j + 1].kind && grid[i][j].kind == grid[i][j - 1].kind) // Pretty straightfoward stuff.
				for (int c = -1; c <= 1; ++c) grid[i][j + c].match++;
		}
	}
}

void gridUpdate(board &grid) {
	for (int i = 9; i >= 0; --i) {
		for (int j = 0; j < 10; ++j) {
			if (grid[i][j].match) {
				for (int n = i; n >= 0; --n) {
					if (grid[n][j].match == 0) {
						swap(grid[n][j].kind, grid[i][j].kind); // If a match is decteted, move the above gems down...
						for (int i = 1; i <= 10; ++i) // ...by swapping the matched gems up.
							for (int j = 1; j <= 10; ++j)
								grid[i][j].match = 0;
						matchFinding(grid); // Re-calculate the matches.
						break;
					}
				}
			}
		}
	}
	for (int i = 0; i < 10; ++i) {
		for (int j = 9; j >= 0; --j) {
			if (grid[i][j].match) {
				grid[i][j].kind = rand() % 6 + 1; // The moved gems now needs to be reinitialized (faking the 'move down' stuff...)
				for (int i = 1; i <= 10; ++i)
					for (int j = 1; j <= 10; ++j)
						grid[i][j].match = 0;
				matchFinding(grid); // Re-calculate the matches.
			}
		}
	}
}