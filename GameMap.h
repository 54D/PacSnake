#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <string>

#include <entities/Entity.h>

class GameMap {

public:
	enum class TerrainState {
		EMPTY,				///< Location is empty.
		BLOCKED,			///< Location is blocked by terrain.
		SNAKE_OCCUPIED,		///< Location is occupied by a Snake. Only used during Entity generation for collision avoidance.
		GHOST_OCCUPIED, 	///< Location is occupied by a Ghost. Only used during Entity generation for collision avoidance.
		FRUIT_OCCUPIED, 	///< Location is occupied by a Fruit. Only used during Entity generation for collision avoidance.
		POWERUP_OCCUPIED	///< Location is occupied by a PowerUp. Only used during Entity generation for collision avoidance.
	};
	static const char TERRAIN_EMPTY_CHAR {' '};
	static const char TERRAIN_BLOCKED_CHAR {'#'};

	/**
	 * Constructor for GameMap.
	 */
	GameMap();
	/**
	 * Destructor for GameMap.
	 */
	~GameMap();

	/**
	 * Obtain the number of rows in this GameMap.
	 * @return	num_rows	Number of rows.
	 */
    int get_num_rows() const;
	/**
	 * Obtain the number of columns in this GameMap.
	 * @return	num_cols	Number of columns.
	 */
    int get_num_cols() const;
	/**
	 * Obtain the TerrainState of specified coordinate in this GameMap.
	 * @param	row				Row index for lookup.
	 * @param	col				Column index for lookup.
	 * @return	terrain_state	TerrainState of the specified coordinate.
	 */
    TerrainState get_terrainState(int row,int col) const;

	/**
	 * Sets the TerrainState of specified coordinate in this GameMap.
	 * @param	row				Row index for lookup.
	 * @param	col				Column index for lookup.
	 * @param	terrain_state	New TerrainState of the specified coordinate.
	 */
	void set_terrainState(int row, int col, TerrainState state);

	/**
	 * Loads a terrain map from a file into this GameMap.
	 * @param	filename	Path of the resource.
	 */
	void load_terrian_map(const std::string& filename);

private:

	int num_rows {0}, num_cols {0};
	TerrainState** terrain_map {nullptr};
	std::vector<Entity*> obstacle;

};

#endif // GAMEMAP_H
