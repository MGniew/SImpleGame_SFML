#ifndef PROJEKTSO_EYE_H
#define PROJEKTSO_EYE_H
#include "Enemy.h"

class Eye :public Enemy {
public:
    Eye(void);
    Eye(int i, int j, Cube ***map);
    ~Eye(void);
    void virtual move();
    void virtual run();
};


#endif //PROJEKTSO_EYE_H
