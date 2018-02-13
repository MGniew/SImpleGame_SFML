#include "Cube.h"

Cube::Cube(void)
{
    if(!texture.loadFromFile("FontImages/cubes.png")) {
        printf("cube.png");
        return;
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,40,40));

}

Cube::Cube(int posX, int posY, char a) : Cube()  {

    x=posX;
    y=posY;

    isWall = (a == 'w' || a == 'x');
    type=a;

    switch(type) {
        case 'w': sprite.setTextureRect(sf::IntRect(0,0,40,40)); break;
        case 'x': sprite.setTextureRect(sf::IntRect(240,0,40,40)); break;
        case 'e': sprite.setTextureRect(sf::IntRect(200,0,40,40)); break;
        case 'k': sprite.setTextureRect(sf::IntRect(125,0,35,40)); break;
        case 'm': sprite.setTextureRect(sf::IntRect(160,0,35,40)); break;
        default:  sprite.setTextureRect(sf::IntRect(0,0,40,40)); break;
    }

}

Cube::~Cube(void)
{
}

void Cube::setPosition(int a, int b)
{
    sprite.setPosition(b*y,a*x);
}


void Cube::collect()
{
    type=' ';
}


