#include <vector>
#include <string>
#include <fstream>
#include <QDebug>

#include <Qt>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include "GameMap.h"
#include <entities/Entity.h>

/* PUBLIC */

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

GameMap::TerrainState GameMap::get_terrainState(int row, int col) const {
	// Out-of-game_map are all BLOCKED
	if (row < 0 || row >= num_rows || col < 0 || col >= num_cols)
		return GameMap::TerrainState::BLOCKED;
    return terrain_map[row][col];
}

void GameMap::set_terrainState(int row, int col, TerrainState state) {
	terrain_map[row][col] = state;
}

void GameMap::load_terrian_map(const std::string& filename) {
    // Remove previous content
    for (int i = 0; i < num_rows; i++)
        delete [] terrain_map[i];
    delete [] terrain_map;
    terrain_map = nullptr;

    // Delete elements in
    if (obstacle.size() > 0) {
        for (auto it = obstacle.begin(); it != obstacle.end(); it++) {
            delete (*it);
        }
        obstacle.clear();
    }

    // File Input
    QFile terrain_map_file(QString::fromStdString(filename));
    if (!terrain_map_file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    QTextStream input(&terrain_map_file);
    input >> num_rows >> num_cols;
    input.skipWhiteSpace();

    // Create map
    terrain_map = new TerrainState* [num_rows];
    for (int row = 0; row < num_rows; row++) {
        terrain_map[row] = new TerrainState [num_cols];
    }

    // Input map and create obstacle object
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            char current_character;
            input >> current_character;
            switch (current_character) {
                case TERRAIN_EMPTY_CHAR:
                    terrain_map[row][col] = TerrainState::EMPTY;
                    break;
                case TERRAIN_BLOCKED_CHAR:
                    terrain_map[row][col] = TerrainState::BLOCKED;
                    // Create obstacle object
                    Entity* temp_obstacle = new Entity(row, col);
                    obstacle.push_back(temp_obstacle);
                    break;
            }
        }
        input.skipWhiteSpace();
	}

    // Close File
    terrain_map_file.close();
}

void GameMap::update_terrain_map(std::vector<GameMap::terrain_info>& game_map_info) {
	for (int row = 0; row < num_rows; row++) {
		for (int col = 0; col < num_cols; col++) {
			if(terrain_map[row][col] != TerrainState::BLOCKED)
				terrain_map[row][col] = TerrainState::EMPTY;
		}
	}
	for (auto it = game_map_info.begin(); it != game_map_info.end(); it++) {
		terrain_map[(*it).row][(*it).col] = (*it).state;
	}
	for (auto it = obstacle.begin(); it != obstacle.end(); it++) {
		terrain_map[(*it)->get_row()][(*it)->get_col()] = TerrainState::BLOCKED;
	}
}
