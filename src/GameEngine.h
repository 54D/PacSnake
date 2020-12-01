#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "GameMap.h"
#include <entities/fruits_and_powerUps/PowerUp.h>

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	void run_game();

private:
	void temp_load_game();
	void temp_print_snake_status() const;
	void temp_process_game();
	
	bool is_game_over() const;
	
	GameMap game_map;
	Snake* snake;
	std::vector<PowerUp*> powerUps;
};


#endif /* GAMEENGINE_H */