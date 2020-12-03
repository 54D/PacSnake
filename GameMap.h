#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <string>

#include <entities/Entity.h>

class GameMap {
public:
	// Note that TerrainState::OCCUPIED only used for Entity generation to avoid colliding
	enum class TerrainState { EMPTY, BLOCKED, OCCUPIED };
	static const char TERRAIN_EMPTY_CHAR {' '};
	static const char TERRAIN_BLOCKED_CHAR {'#'};

    int get_num_rows() const;
    int get_num_cols() const;
    TerrainState get_terrainState(int row,int col) const;

	void set_terrainState(int row, int col, TerrainState state);

	void load_terrian_map(const std::string& filename);

	GameMap();
	~GameMap();
private:
	int num_rows {0}, num_cols {0};
	TerrainState** terrain_map {nullptr};
	std::vector<Entity*> obstacle;
};

#endif // GAMEMAP_H
