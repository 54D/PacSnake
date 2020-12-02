#include <vector>
#include <string>
#include <fstream>

#include "GameMap.h"
#include <entities/Entity.h>

GameMap::GameMap() {}

GameMap::~GameMap() {
	// Delete terrain map
	for (int i = 0; i < num_rows; i++)
		delete [] terrain_map[i];
	delete [] terrain_map;
	terrain_map = nullptr;

	// Delete elements in obstacle
	for (auto it = obstacle.begin(); it != obstacle.end(); it++) {
		delete (*it);
	}
	obstacle.clear();
}

int GameMap::get_num_rows() const {
    return num_rows;
}
int GameMap::get_num_cols() const {
    return num_cols;
}

void GameMap::load_terrian_map(const std::string& filename) {
	// Remove previous content
	for (int i = 0; i < num_rows; i++)
		delete [] terrain_map[i];
	delete [] terrain_map;
	terrain_map = nullptr;

	// Delete elements in obstacle
	for (auto it = obstacle.begin(); it != obstacle.end(); it++) {
		delete (*it);
	}
	obstacle.clear();

	// File Input
	std::ifstream terrain_map_file(filename);
	if (!terrain_map_file)
			return;

	terrain_map_file >> num_rows >> num_cols;
	terrain_map_file >> std::ws;
	terrain_map_file >> std::noskipws;

	// Create map
	terrain_map = new TerrainState* [num_rows];
	for (int row = 0; row < num_rows; row++) {
		terrain_map[row] = new TerrainState [num_cols];
	}

	// Input map and create obstacle object
	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			char current_character;
			terrain_map_file >> current_character;
			switch (current_character) {
				case TERRAIN_EMPTY_CHAR:
					terrain_map[row][col] = TerrainState::EMPTY;
					break;
				case TERRAIN_BLOCKED_CHAR:
					terrain_map[row][col] = TerrainState::BLOCKED;
					// Create obstacle object
					// TODO: Add image
					Entity* temp_obstacle = new Entity(row, col);
					obstacle.push_back(temp_obstacle);
					break;
			}
		}
		terrain_map_file >> std::ws;
	}
}
