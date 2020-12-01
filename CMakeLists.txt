cmake_minimum_required(VERSION 3.17)
project(PacSnake)

include_directories(merge_folder/src)

set(CMAKE_CXX_STANDARD 11)

add_executable( PacSnake merge_folder/main.cpp
                merge_folder/src/entities/Entity.cpp merge_folder/src/entities/Entity.h
                merge_folder/src/entities/MovingEntity.cpp merge_folder/src/entities/MovingEntity.h
                merge_folder/src/entities/snake/SnakeBody.cpp merge_folder/src/entities/snake/SnakeBody.h
                merge_folder/src/entities/snake/Snake.cpp merge_folder/src/entities/snake/Snake.h
                merge_folder/src/entities/fruits_and_powerUps/Fruit.h
                merge_folder/src/entities/fruits_and_powerUps/PowerUp.cpp merge_folder/src/entities/fruits_and_powerUps/PowerUp.h
                merge_folder/src/entities/fruits_and_powerUps/PU_Dash.cpp merge_folder/src/entities/fruits_and_powerUps/PU_Dash.h
                merge_folder/src/GameMap.cpp merge_folder/src/GameMap.h
                merge_folder/src/GameEngine.cpp merge_folder/src/GameEngine.h merge_folder/src/entities/fruits_and_powerUps/PuShield.cpp merge_folder/src/entities/fruits_and_powerUps/PuShield.h merge_folder/src/entities/ghosts/GhostBody.cpp merge_folder/src/entities/ghosts/GhostBody.h merge_folder/src/entities/ghosts/NormalGhost.cpp merge_folder/src/entities/ghosts/NormalGhost.h)