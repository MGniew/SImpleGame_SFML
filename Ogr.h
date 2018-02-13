#ifndef PROJEKTSO_OGR_H
#define PROJEKTSO_OGR_H

#include "Enemy.h"
class Ogr :
        public Enemy
{
public:
    Ogr(void);
    Ogr(int i, int j, Cube ***map);
    ~Ogr(void);
    void virtual move();
    void virtual run();
};


#endif //PROJEKTSO_OGR_H
