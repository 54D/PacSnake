#include <string>
#include "Stats.h"

Stats::Stats() = default;

void Stats::update_fruits_eaten(int num){
    fruits_eaten = num;
}

void Stats::add_in_game_distance(){
    in_game_distance++;
}

void Stats::update_survival_time(long time){
    survival_time = time;
}

void Stats::update_snake_length(int length){
    longest_snake_length = length;
}
