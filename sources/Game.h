#ifndef PROJEKTSO_GRA_H
#define PROJEKTSO_GRA_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "Location.h"
#include "Engine.h"

using namespace std;
using namespace sf;

class Game {
public:
    Game();
    ~Game();
    void Run();
    void Play();
protected:
    enum Status {MENU, PLAYING, END};
    Status status;
private:
    Font font;
    void MainMenu();
};


#endif PROJEKTSO_GRA_H
