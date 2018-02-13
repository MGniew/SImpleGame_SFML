#include "Ogr.h"
#include "Location.h"

Ogr::Ogr(void) {

    if(!texture.loadFromFile("FontImages/ogr.png")) {
        printf("ogr.png");
        return;
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,40,40));

    speed=20;
    direction=1;
    type='1';

}

Ogr::~Ogr(void) {

}

void Ogr::move() {

}

void Ogr::run() {

    while (!threadStop) {
        if (mutex->try_lock()) {
            if (map[x + direction][y] == NULL) {
                map[x + direction][y] = map[x][y];
                map[x][y] = NULL;
                x += direction;
                setPosition(Location::cube_width, Location::cube_height);
            } else if (map[x + direction][y]->type == 'p') {
                dynamic_cast<Player *>(map[x + direction][y])->operator--();
                map[x + direction][y] = map[x][y];
                map[x][y] = NULL;
                x += direction;
                setPosition(Location::cube_width, Location::cube_height);
            } else
                changeDirection();
            mutex->unlock();
            this_thread::sleep_for(chrono::milliseconds(400));
        }

    }
}

Ogr::Ogr(int i, int j, Cube ***map) : Ogr() {
    x=i;
    y=j;
    this->map=map;
}
