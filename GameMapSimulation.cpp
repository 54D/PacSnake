#include <iostream>		// For display map
#include <windows.h>	// For display map, suggested to remove for real project

#include "GameMapSimulation.h"
#include <entities/snake/SnakeBody.h>
#include <entities/snake/Snake.h>

using namespace std;	// For display map, suggested to remove for real project

GameMapSimulation::GameMapSimulation() {}

GameMapSimulation::~GameMapSimulation() {}

void GameMapSimulation::temp_create_map() {
	num_row = num_col = 100;
	
	// Create obstacle
}

// Temp function for display map
static void gotoxy(int row, int col) {
	COORD c;
	c.X = col;
	c.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void GameMapSimulation::temp_print_map(Snake* snake) const {
	
	// Clear screen
	system("cls");
	
	// Print snake on map
	const SnakeBody* currentSnakeBody = snake;
	while (currentSnakeBody != nullptr) {
		gotoxy(currentSnakeBody->get_row(), currentSnakeBody->get_col());
		cout << static_cast<int>(currentSnakeBody->get_headingDirection());
		currentSnakeBody = currentSnakeBody->get_next();
	}
}
