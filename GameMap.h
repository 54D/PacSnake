#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <entities/snake/Snake.h>

class GameMap {
public:
	enum class TerrainState { EMPTY, BLOCKED, OCCUPIED };
	GameMap();
	~GameMap();
	
	void temp_create_map();
	void temp_print_map(Snake* snake) const;
	
private:
	int num_row;
	int num_col;
	// obstacle;
};


#endif /* GAMEMAP_H */
