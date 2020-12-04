#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>
#include "Stats.h"

class Achievement : public Stats
{
public:
    /**
     * Constructor for Achievement.
     * Read game statistics from the local file
     */
    Achievement(std::string);
    /**
     * Write the current data into the local achievement file
     * location: (currentbuildfile)/stat.txt
     */
    void update_achievement_file();
    /**
     * Comparing the statistics between the current game and the local file and save the highest one
     */
    void compare_stat(Stats temp);

private:
    std::string path;
};

#endif // ACHIEVEMENT_H
