#ifndef PROJEKTSO_MOVABLEOBJECT_H
#define PROJEKTSO_MOVABLEOBJECT_H
#include "Cube.h"
#include "Top.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include "mutex"
using namespace sf;
using namespace std;

class MovableObject : public Cube
{

public:

    MovableObject(void);
    MovableObject(Cube ***map);
    ~MovableObject(void);
    void start(std::mutex *mutex);
    virtual void run() = 0;
    thread thr;
    bool threadStop;
    Cube ***map;
    std::mutex *mutex;

protected:
    float speed;
    int direction; // 0-N,1-E,2-S,3-W

};

#endif //PROJEKTSO_MOVABLEOBJECT_H
