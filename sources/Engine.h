#ifndef PROJEKTSO_ENGINE_H
#define PROJEKTSO_ENGINE_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <thread>
#include "Maze.h"
#include "Location.h"
#include "Cube.h"
#include <thread>
#include <mutex>

using namespace sf;

class Engine {

private:

    Music music;
    SoundBuffer doorSoundBuffer;
    Sound doorSound;
    Font font;

    Maze maze;
    int xCurrTop;
    int yCurrTop;

    Location *location;

    bool winner;
    bool exitToMenu;

    bool keysPressed[4];

    std::mutex m;
    std::mutex mMove;

    Player* player;

public:
    Engine(sf::RenderWindow &win);
    ~Engine(void);


    void run(sf::RenderWindow &window);
    void setMap(const char *a);
    void destroyLocation();
    void loadLocation();
    void showText(sf::RenderWindow &window, sf::Color clearColor, const char* a, sf::Color textColor, int time);
    bool fileExists(const char *fileName);
    bool saveMap(string fileName);
};


#endif
