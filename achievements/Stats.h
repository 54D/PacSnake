#ifndef STAT_H
#define STAT_H


class Stats
{
public:
    Stats();
    void add_in_game_distance();
    void update_survival_time(long time);
    void update_fruits_eaten(int num);
    void update_snake_length(int length);

private:
    int in_game_distance = 0;
    long survival_time = 0;
    int fruits_eaten = 0;
    int longest_snake_length = 0;
};

#endif // STAT_H
