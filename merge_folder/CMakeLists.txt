cmake_minimum_required(VERSION 3.17)
project(PacSnake)

include_directories(src)

set(CMAKE_CXX_STANDARD 11)

add_executable(PacSnake main.cpp src/entities/Entity.cpp src/entities/Entity.h src/entities/MovingEntity.cpp src/entities/MovingEntity.h src/entities/snake/SnakeBody.cpp src/entities/snake/SnakeBody.h src/entities/snake/Snake.cpp src/entities/snake/Snake.h src/entities/fruits_and_powerUps/Fruit.h src/entities/fruits_and_powerUps/PowerUp.cpp src/entities/fruits_and_powerUps/PowerUp.h src/entities/fruits_and_powerUps/PU_Dash.cpp src/entities/fruits_and_powerUps/PU_Dash.h src/GameMap.cpp src/GameMap.h src/GameEngine.cpp src/GameEngine.h)