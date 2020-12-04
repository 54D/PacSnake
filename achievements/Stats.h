#ifndef STAT_H
#define STAT_H


class Stats
{
public:
    Stats();
    void update_in_game_distance(int distance);
    void update_survival_time(long time);
    void update_fruits_eaten(int num);
    void update_snake_length(int length);
    void update_play_count(int count);

    int get_ingame_distance();
    long get_survival_time();
    int get_fruits_eaten();
    int get_longest_snake_length();
    int get_play_count();


private:
    int in_game_distance = 0;
    long survival_time = 0;
    int fruits_eaten = 0;
    int longest_snake_length = 0;
    int play_count = 0;
};

#endif // STAT_H
