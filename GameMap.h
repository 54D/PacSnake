#ifndef GAMEMAP_H_
#define GAMEMAP_H_

class GameMap {
public:
	enum class TerrainState {EMPTY, BLOCKED, OCCUPIED};

	GameMap();
	~GameMap();
	
private:
	int num_row, num_col;
};

#endif /* GAMEMAP_H_ */