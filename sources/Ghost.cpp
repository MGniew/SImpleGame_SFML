#include "Ghost.h"
#include "Location.h"

Ghost::Ghost(void) {

    if(!texture.loadFromFile("FontImages/ghost.png")) {
        printf("ghost.png");
        return;
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,40,40));

    speed=20;
    direction=1;
    type='3';

}

Ghost::~Ghost(void) {

}

void Ghost::move() {

}

void Ghost::run() {
    int randomDirecion;
    int xi, yi;

    while (!threadStop) {

        xi = 0;
        yi = 0;
        randomDirecion = rand() % 4;
        switch (randomDirecion) {
            case 0: xi=-1; break;
            case 1: xi=1; break;
            case 2: yi=-1; break;
            case 3: yi=1; break;
            default: break;
        }

        if (mutex->try_lock()) {
            if (map[x + xi][y + yi] == NULL) {
                map[x + xi][y + yi] = map[x][y];
                map[x][y] = NULL;
                x += xi;
                y += yi;
                setPosition(Location::cube_width, Location::cube_height);
            } else if (map[x + xi][y + yi]->type == 'p') {
                dynamic_cast<Player *>(map[x + xi][y + yi])->operator--();
                map[x + xi][y + yi] = map[x][y];
                map[x][y] = NULL;
                x += xi;
                y += yi;
                setPosition(Location::cube_width, Location::cube_height);
            }
            mutex->unlock();
            this_thread::sleep_for(chrono::milliseconds(400));
        }
    }
}

Ghost::Ghost(int i, int j, Cube ***map) : Ghost() {
    x=i;
    y=j;
    this->map=map;
}
