// PF162A01 - Spring 2017
// BOSTON CRUSH SAGA
// This game uses SFML, included are the dll files
// This game uses free sprites/fonts on the Internet
// Some of the code here are referenced from GitHub (the mouse click event handler)
// In this game, I used the tutorial here: https://eeprogrammer.wordpress.com/2015/03/27/sfml-draw-image-and-text/ to draw the game elements.
#include <SFML/Graphics.hpp>
#include <time.h>
#include <sstream>
#include <string>
#include "User.h"
#include <Windows.h>
using namespace sf;

int tileSize = 54; // Tile size
Vector2i offset(24, 48); // The first tile begin at (24,48)

struct piece {
	int x, y; // The coordiantes of the gems in the window.
	int col, row;
	int kind;
	int match; // When 1, it indicates that a match has been found.
	piece() { match = 0; }
} board[10][10]; // Although this game uses only an 8x8 table, I used 10x10 to advoid some problems that may occur when the gems are at the border

void swap(piece p1, piece p2) {
	std::swap(p1.col, p2.col);
	std::swap(p1.row, p2.row);

	board[p1.row][p1.col] = p1; // After we swap the values...
	board[p2.row][p2.col] = p2; // ...we have to reassign the gems.
}

int main() {
	bool flag = true;
	srand(time(NULL)); // Seed for rand() function
	user user;
	user.importName("user.dat");

	RenderWindow game(VideoMode(480, 640), "Boston Crush Saga"); // Initialize a render window, size is 480x640, window title is "Boston Crush Saga".
	game.setFramerateLimit(60); // Set framerate to 60.

	Texture bg, gem;
	bg.loadFromFile("resources/ui_assets/bg.png"); // Texture for background
	gem.loadFromFile("resources/characters/gems.png");

	Sprite background(bg), gems(gem);

	Font font;

	font.loadFromFile("resources/font/HVD_Comic_Serif_Pro.otf");

	for (int i = 1; i <= 8; i++)
		for (int j = 1; j <= 8; j++) {
			board[i][j].kind = rand() % 7;
			board[i][j].row = i;
			board[i][j].col = j;
			board[i][j].x = j*tileSize; // Setting coordinates for the gems in the render window.
			board[i][j].y = i*tileSize;
		}

	int x1, y1, x2, y2;
	int click = 0;
	Vector2i pos;
	bool isSwap = false, isMoving = false;
	int nMoves = user.getMoves(), nScore = 0;

	while (game.isOpen()) {
		// Showing number of moves left
		std::ostringstream oss;
		oss << nMoves << " move(s) left";
		Text n_moves;
		n_moves.setFont(font);
		n_moves.setCharacterSize(24);
		// Showing score
		std::ostringstream n_score;
		n_score << "Score: " << nScore * 100;
		Text scoreDisp;
		scoreDisp.setFont(font);
		scoreDisp.setCharacterSize(24);
		
		Event event;
		while (game.pollEvent(event)) {
			if (event.type == Event::Closed)
				game.close();
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					if (!isSwap && !isMoving) click++; // On left mouse press, increase click by 1.
					pos = Mouse::getPosition(game) - offset;
				}
			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Q) return 0;
		}
		// Handles mouse click
		if (click == 1) {
			x1 = pos.x / tileSize + 1;
			y1 = pos.y / tileSize + 1;
		}
		if (click == 2) {
			x2 = pos.x / tileSize + 1;
			y2 = pos.y / tileSize + 1;
			if (abs(x1 - x2) + abs(y1 - y2) == 1) { // The second gem must be  adjecent to the first.
				swap(board[y1][x1], board[y2][x2]);
				isSwap = true;
				nMoves--; // On successful swap, decrease the number of moves by 1.
				click = 0;
			}
			else click = 1;
		}
		// Match finding
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++) {
				if (board[i][j].kind == board[i - 1][j].kind && board[i][j].kind == board[i + 1][j].kind)
					for (int n = -1; n <= 1; n++) board[i + n][j].match++;
				if (board[i][j].kind == board[i][j - 1].kind && board[i][j].kind == board[i][j + 1].kind)
					for (int n = -1; n <= 1; n++) board[i][j + n].match++;
			}
		// Move animation
		isMoving = false;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++) {
				piece &p = board[i][j]; // We use p here for conveniece.
				int dx, dy;
				for (int n = 0; n < 5; n++) { // 5 - speed.
					dx = p.x - p.col*tileSize; // dx/dy is the distance between the gem's current position and it's intended position...
					dy = p.y - p.row*tileSize; // ... each frame will move the gem down by 5 pixels.
					if (dx) p.x -= dx / abs(dx); // Until dx/dy is 0 - which means that the gem has arrived.
					if (dy) p.y -= dy / abs(dy);
				}
				if (dx || dy) isMoving = true; // While it is moving, we skip the part below (where !isMoving is present).
			}
		// Get score. Note that score here is NOT the actual game score, but rather a temporary value to determine whether a match has been made.
		int score = 0;
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++)
				score += board[i][j].match;
		// Swap back if no match found
		if (isSwap && !isMoving) {
			if (!score) swap(board[y1][x1], board[y2][x2]);
			isSwap = false;
		}
		// Update grid
		if (!isMoving) {
			for (int i = 8; i >= 1; i--)
				for (int j = 1; j <= 8; j++) {
					if (board[i][j].match) {
						for (int n = i; n >= 1; n--)
							if (!board[n][j].match) {
								swap(board[n][j], board[i][j]); // This will swap the gem with the ones above it, and has no match with it.
								break;
							}
					}
				}	

			for (int j = 1; j <= 8; j++)
				for (int i = 8, n = 0; i >= 1; i--)
					if (board[i][j].match) {
						nScore++;
						board[i][j].kind = rand() % 7; // Randomize the kind of the new gem.
						board[i][j].y = -tileSize*n; // This will move the gems down. When n = 0; it will spawn the new gem at the top border.
						board[i][j].match = 0; // We will also reset the match. It will be calculated again.
						n++;
					}
		}
		// App draw
		game.draw(background);
		for (int i = 1; i <= 8; i++)
			for (int j = 1; j <= 8; j++) {
				piece p = board[i][j];
				gems.setTextureRect(IntRect(p.kind * 48, 0, 48, 48)); // Extract the correct model from the sprite sheet.
				gems.setColor(Color(255, 255, 255));
				gems.setPosition(p.x, p.y);
				gems.move(offset.x - tileSize, offset.y - tileSize);
				game.draw(gems);
			}

		n_moves.setString(oss.str());
		n_moves.setPosition(24, 490);
		scoreDisp.setString(n_score.str());
		scoreDisp.setPosition(24, 520);
		game.draw(n_moves); // Draw number of moves left.
		game.draw(scoreDisp); // Draw score.
		// When out of moves
		Text over;
		over.setFont(font);
		over.setCharacterSize(64);
		over.setString("Game Over");
		if (!nMoves && flag && !isMoving) {
			user.setScore(nScore * 100);
			user.exportScore("score.dat", nScore * 100);
			flag = false;
		}
		if (!nMoves) {
			game.clear(Color(255, 255, 255, 255));
			game.draw(background);
			over.setPosition(58, 24);
			game.draw(over);
			scoreDisp.setPosition(180, 100);
			game.draw(scoreDisp);
		}
		game.display();
	}
	return 0;
}