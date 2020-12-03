#ifndef GAMEENGINESIMULATION_H
#define GAMEENGINESIMULATION_H

#include <vector>

#include "GameMapSimulation.h"
#include <entities/fruits_and_powerUps/PowerUp.h>

class GameEngineSimulation {
public:
	GameEngineSimulation();
	~GameEngineSimulation();
	void run_game();

private:
	void temp_load_game();
	void temp_print_snake_status() const;
	void temp_process_game();
	
	bool is_game_over() const;
	
    GameMapSimulation game_map;
	Snake* snake;
	std::vector<PowerUp*> powerUps;
};


#endif /* GAMEENGINESIMULATION_H */
