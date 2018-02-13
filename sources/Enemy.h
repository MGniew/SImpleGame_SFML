#ifndef PROJEKTSO_ENEMY_H
#define PROJEKTSO_ENEMY_H

#include "MovableObject.h"
class Enemy : public MovableObject {

public:
    int direction;
    void changeDirection();
    Enemy(void);
    ~Enemy(void);
    virtual void move()=0;
    virtual void run()=0;
};


#endif //PROJEKTSO_ENEMY_H
