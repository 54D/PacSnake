#ifndef ACHIEVEMENT_H
#define ACHIEVEMENT_H

#include <string>
#include "Stats.h"

class Achievement : public Stats
{
public:
    Achievement(std::string);
    void update_achievement_file();

private:
    std::string path;
};

#endif // ACHIEVEMENT_H
