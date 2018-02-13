#ifndef PROJEKTSO_GHOST_H
#define PROJEKTSO_GHOST_H

#include "Enemy.h"
class Ghost : public Enemy
{
public:
    Ghost(void);
    Ghost(int i, int j, Cube ***map);
    ~Ghost(void);
    void virtual move();
    void virtual run();
};


#endif //PROJEKTSO_GHOST_H