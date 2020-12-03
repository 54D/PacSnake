#include <iostream>		// For display
#include <windows.h>	// For display, suggested to remove for real project
#include <deque>

#include "GameEngineSimulation.h"
#include <entities/MovingEntity.h>
#include <entities/snake/Snake.h>
#include <entities/fruits_and_powerUps/PowerUp.h>
#include <entities/fruits_and_powerUps/PU_Dash.h>

using namespace std;	// For display map, suggested to remove for real project

GameEngineSimulation::GameEngineSimulation() {}
GameEngineSimulation::~GameEngineSimulation() {
	delete snake;
}

void GameEngineSimulation::run_game() {
	temp_load_game();
	temp_process_game();
}

void GameEngineSimulation::temp_load_game() {
	// Initialise everything
	// TODO: Load game map
	game_map.temp_create_map();
	
	// TODO: Create ghost
	
	// Create snake
	snake = new Snake {10, 70};
}

// Temp function for display snake status, suggested to remove for real project
static void gotoxy(int row, int col) {
	COORD c;
	c.X = col;
	c.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void GameEngineSimulation::temp_print_snake_status() const {
	gotoxy(0, 0);
	// Print health
	cout << "HEALTH: " << snake->get_health() << " / " << snake->get_health() << endl;
	// Print speed
	cout << "SPEED: " << snake->get_speed() << endl;
	
	// Print power up inventory
	deque<PowerUp*> inventory = snake->get_pu_inventory();
	cout << "Power Up Inventory( " << inventory.size() << "): " << endl;
	for (auto it = inventory.begin(); it != inventory.end(); it++) {
		cout << (*it) << " ";
	}
	cout << endl;
	// Print current power up activating
	cout << " Current Power Up: " << (snake->get_pu_activate()) << endl;
	cout << "================================" << endl;
	cout << "Snake Body coord: " << endl;
	const SnakeBody* currentSnakeBody = snake;
	while (currentSnakeBody != nullptr) {
		if (currentSnakeBody == snake)
			cout << currentSnakeBody->get_row() << "\t" << currentSnakeBody->get_col() << "\t" << currentSnakeBody->get_prev() << "\t\t" << currentSnakeBody << "\t" << currentSnakeBody->get_next() <<endl;
		else
			cout << currentSnakeBody->get_row() << "\t" << currentSnakeBody->get_col() << "\t" << currentSnakeBody->get_prev() << "\t" << currentSnakeBody << "\t" << currentSnakeBody->get_next() <<endl;
		currentSnakeBody = currentSnakeBody->get_next();
	}
	cout << endl;
}

void GameEngineSimulation::temp_process_game() {
	while (!is_game_over()) {
		game_map.temp_print_map(snake);
		temp_print_snake_status();
		cout << "=============================================" << endl;
		cout << "Choose action (First character of the word)" << endl;
		cout << "Move / North / East / South / West" << endl;
		cout << "Increase length by 1 / Remove length from index" << endl;
		cout << "Power up" << endl;
		cout << "Game over" << endl;
		cout << endl;
		cout << "Your action:" << endl;
		char action;
		cin >> action;
		switch (action) {
			case 'm':
				snake->move_forward();
				break;
			case 'n':
				snake->set_headingDirection(MovingEntity::Direction::NORTH);
				snake->move_forward();
				break;
			case 'e':
				snake->set_headingDirection(MovingEntity::Direction::EAST);
				snake->move_forward();
				break;
			case 's':
				snake->set_headingDirection(MovingEntity::Direction::SOUTH);
				snake->move_forward();
				break;
			case 'w':
				snake->set_headingDirection(MovingEntity::Direction::WEST);
				snake->move_forward();
				break;
			case 'i':
				snake->increase_length(1);
				break;
			case 'r':
				cout << "Enter index: ";
				int index;
				cin >> index;
				snake->remove_tail(index);
				break;
			case 'p':
				cout << "Enter power up (d): ";
				char pu;
				cin >> pu;
				switch (pu) {
					case 'd':
						// Simulate a power up is created and being eaten by the snake and being used after it moves 1 step
						
						// A power up is first randomly generated on map
						PU_Dash* dash = new PU_Dash (0, 0);
						// Store the power up on the map in a vector of game
						powerUps.push_back(dash);
						
						// Power up being eaten by snake (collision check)
						/* for (auto it = powerUps.begin(); it != powerUps.end(); it++)
						 * 	if collision -> emit signal
						 * */
						// Add to inventory and remove from game engine
						snake->addPUToInventory(dash);
						for (auto it = powerUps.begin(); it != powerUps.end(); it++){
							if (*it == dash){
								powerUps.erase(it);
								break;
							}
						}
						
						// Check if power up successfully added to inventory of snake
						game_map.temp_print_map(snake);
						temp_print_snake_status();
						cout << "Input anything to use the power up" << endl;
						system("pause");
						
						snake->usePU();
						
						game_map.temp_print_map(snake);
						temp_print_snake_status();
						cout << "Input anything to use the move forward (1 time)" << endl;
						system("pause");
						
						snake->move_forward();
						game_map.temp_print_map(snake);
						temp_print_snake_status();
						cout << "Input anything to use the move forward (2 times)" << endl;
						system("pause");
						
						snake->move_forward();
						game_map.temp_print_map(snake);
						temp_print_snake_status();
						cout << "Input anything to deactivate" << endl;
						system("pause");
						
						dash->deactivate(snake);
						delete dash;
						game_map.temp_print_map(snake);
						temp_print_snake_status();
						cout << "Deactivated" << endl;
						system("pause");
						
						break;
				}
				break;
			case 'g':
				snake->set_health(0);
				break;
		}
	}
	system("pause");
}

bool GameEngineSimulation::is_game_over() const {
	if (snake->get_health() <= 0)
		return true;
	return false;
}
