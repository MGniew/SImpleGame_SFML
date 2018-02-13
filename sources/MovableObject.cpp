#include "MovableObject.h"

MovableObject::MovableObject(void) : thr() {

}


MovableObject::~MovableObject(void)
{
    threadStop=true;
    if (thr.joinable())
        thr.join();
}

void MovableObject::start(std::mutex *mutex) {
    this->mutex = mutex;
    thr = std::thread (&MovableObject::run, this);
    threadStop = false;
}

MovableObject::MovableObject(Cube ***map) {
    this->map=map;
}

