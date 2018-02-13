#include "Door.h"

Door::Door(int i, int j, bool isOpen) {

    if(!texture.loadFromFile("FontImages/cubes.png"))
    {
        printf("cubes.png");
        return;
    }
    sprite.setTexture(texture);
    isOpen?sprite.setTextureRect(sf::IntRect(80,0,40,40)):sprite.setTextureRect(sf::IntRect(40,0,40,40));
    type='d';
    this->isOpen = isOpen;
    x = i;
    y = j;
}

Door::~Door(void) {

}

void Door::open() {
    isOpen = true;
    sprite.setTextureRect(sf::IntRect(80,0,40,40));
}

void Door::setDestination(char d) {
    destination = d;
}

char Door::getDestination() {
    return destination;
}
