#include <iostream>

#include "src/entities/Entity.h"
#include "src/entities/MovingEntity.h"
#include "src/entities/snake/SnakeBody.h"
#include "src/entities/snake/Snake.h"

using namespace std;
int main() {
    Snake* s = new Snake {0.0, 0.0, 1.0};
    const SnakeBody* currentSB = s;
    while (currentSB != nullptr) {
        std::cout << currentSB->get_row() << "\t" << currentSB->get_col() << endl;
        currentSB = currentSB->get_next();
    }
    return 0;
}