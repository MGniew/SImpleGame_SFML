#ifndef PROJEKTSO_DOOR_H
#define PROJEKTSO_DOOR_H
#include "Cube.h"

class Door : public Cube {


    char destination;
public:
    Door(int i, int j, bool isOpen);
    ~Door(void);
    void open();
    void setDestination(char d);
    char getDestination();
    bool isOpen;
};


#endif //PROJEKTSO_DOOR_H
