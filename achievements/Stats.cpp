#include <string>
#include "Stats.h"

Stats::Stats() = default;

void Stats::update_fruits_eaten(int num){
    fruits_eaten = num;
}

void Stats::update_in_game_distance(int distance){
    in_game_distance = distance;
}

void Stats::update_survival_time(long time){
    survival_time = time;
}

void Stats::update_snake_length(int length){
    longest_snake_length = length;
}

int Stats::get_ingame_distance(){
    return in_game_distance;
}
long Stats::get_survival_time(){
    return survival_time;
}

int Stats::get_fruits_eaten(){
    return fruits_eaten;
}
int Stats::get_longest_snake_length(){
    return longest_snake_length;
}

void Stats::update_play_count(int num){
    play_count = num;
}

int Stats::get_play_count(){
    return play_count;
}

