#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <string>

#include <entities/Entity.h>

class GameMap {
public:
	enum class TerrainState { EMPTY, BLOCKED };
	static const char TERRAIN_EMPTY_CHAR {' '};
	static const char TERRAIN_BLOCKED_CHAR {'#'};

	void load_terrian_map(const std::string& filename);

	GameMap();
	~GameMap();
private:
	int num_rows {0}, num_cols {0};
	TerrainState** terrain_map {nullptr};
	std::vector<Entity*> obstacle;
};

#endif // GAMEMAP_H
