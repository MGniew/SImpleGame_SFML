#ifndef PROJEKTSO_CUBE_H
#define PROJEKTSO_CUBE_H

#include <SFML/Graphics.hpp>

using namespace sf;


class Cube: public Sprite
{
protected:
    Cube(void);

    Texture texture;
public:
    char type;
    Sprite sprite;
    Cube(int posX, int posY, char a);
    ~Cube(void);
    void setPosition(int a, int b);
    bool isWall;
    void collect();
    int y;
    int x;
};



#endif //PROJEKTSO_CUBE_H
