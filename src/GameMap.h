#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <entities/snake/Snake.h>

class GameMap {
public:
	GameMap();
	~GameMap();
	
	void temp_create_map();
	void temp_print_map(Snake* snake) const;
	
private:
	double num_row;
	double num_col;
	// obstacle;
};


#endif /* GAMEMAP_H */
