#ifndef GAMEMAP_H_
#define GAMEMAP_H_

class GameMap {
public:
	enum class TerrainState {EMPTY, BLOCKED, OCCUPIED};

	GameMap();
	~GameMap();
	
	int get_num_row() const;
	int get_num_col() const;

private:
	int num_row, num_col;
};

#endif /* GAMEMAP_H_ */