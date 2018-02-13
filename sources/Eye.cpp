#include "Eye.h"
#include "Location.h"

Eye::Eye(void) {

    if(!texture.loadFromFile("FontImages/eye.png")) {
        printf("eye.png");
        return;
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,40,40));

    speed=20;
    direction=1;
    type='2';

}

Eye::~Eye(void) {

}

void Eye::move() {

}

void Eye::run() {
    while (!threadStop) {

        if (mutex->try_lock()) {
            if (map[x][y + direction] == NULL) {
                map[x][y + direction] = map[x][y];
                map[x][y] = NULL;
                y += direction;
                setPosition(Location::cube_width, Location::cube_height);
            } else if (map[x][y + direction]->type == 'p') {
                dynamic_cast<Player *>(map[x][y + direction])->operator--();
                map[x][y + direction] = map[x][y];
                map[x][y] = NULL;
                y += direction;
                setPosition(Location::cube_width, Location::cube_height);
            } else
                changeDirection();
            mutex->unlock();
            this_thread::sleep_for(chrono::milliseconds(400));
        }
    }
}

Eye::Eye(int i, int j, Cube ***map) : Eye() {
    x=i;
    y=j;
    this->map=map;
}
