#ifndef GAMEMAPSIMULATION_H
#define GAMEMAPSIMULATION_H

#include <entities/snake/Snake.h>

class GameMapSimulation {
public:
	enum class TerrainState { EMPTY, BLOCKED, OCCUPIED };
    GameMapSimulation();
    ~GameMapSimulation();
	
	void temp_create_map();
	void temp_print_map(Snake* snake) const;
	
private:
	int num_row;
	int num_col;
	// obstacle;
};


#endif /* GAMEMAPSIMULATION_H */
