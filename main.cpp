// SNADBOX / PLAYGROUND / WHATEVER YOU LIKE TO CALL, JUST USE TO TEST STUFF
#include <iostream>
#include <windows.h>
#include <string>

#include "src/entities/Entity.h"
#include "src/entities/MovingEntity.h"
#include "src/entities/snake/SnakeBody.h"
#include "src/entities/snake/Snake.h"

using namespace std;

void gotoxy(int row,int col) {
    COORD c;
    c.X = col;
    c.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void printMap(Snake* s) {
	system("cls");
	const SnakeBody* currentSB = s;	
	while (currentSB != nullptr) {
        gotoxy(static_cast<int>(currentSB->get_row()), static_cast<int>(currentSB->get_col()));
		cout << static_cast<int>(currentSB->get_headingDirection());
		currentSB = currentSB->get_next();
    };
	
	gotoxy(10, 0);
	currentSB = s;
	cout << s->get_health() << "/" << s->get_max_health() << "\t" << s->get_speed() << "\t" << s->get_length() << endl; 
	cout << "SnakeBody coord: " << endl;
    while (currentSB != nullptr) {
        if (currentSB == s)
			cout << currentSB->get_row() << "\t" << currentSB->get_col() << "\t" << currentSB->get_prev() << "\t\t" << currentSB << "\t" << currentSB->get_next() <<endl;
        else
			cout << currentSB->get_row() << "\t" << currentSB->get_col() << "\t" << currentSB->get_prev() << "\t" << currentSB << "\t" << currentSB->get_next() <<endl;
		currentSB = currentSB->get_next();
    };
}

int main() {
    Snake snakeobj {5.0, 2.0, 1.0};
	Snake* s = &snakeobj;
	char operation;
	do {
		printMap(s);
		cout << "Select operation: ";
		cin >> operation;
		switch (operation) {
			case 'm':
				s->move_forward();
				break;
			case 'n':
				s->set_headingDirection(MovingEntity::Direction::NORTH);
				s->move_forward();
				break;
			case 'e':
				s->set_headingDirection(MovingEntity::Direction::EAST);
				s->move_forward();
				break;
			case 's':
				s->set_headingDirection(MovingEntity::Direction::SOUTH);
				s->move_forward();
				break;
			case 'w':
				s->set_headingDirection(MovingEntity::Direction::WEST);
				s->move_forward();
				break;
			case 'i':
				s->increase_length(1);
				break;
			case 'r':
				int index;
				cout << "Enter index:";
				cin >> index;
				s->remove_tail(index);
				break;
			case 'x':
				cout << "Exit" << endl;	
				break;
			default:
				break;
		}
	} while (operation != 'x');
	system("pause");
    return 0;
}