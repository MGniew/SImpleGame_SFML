#ifndef PROJEKTSO_PLAYER_H
#define PROJEKTSO_PLAYER_H
#include <SFML/Audio.hpp>
#include "MovableObject.h"
#include "Location.h"
#include <iostream>


using namespace sf;
using namespace std;

class Player : public MovableObject {

public:
    SoundBuffer moveSoundBuffer;
    Sound moveSound;
    SoundBuffer dieSoundBuffer;
    Sound dieSound;
    SoundBuffer coinSoundBuffer;
    Sound coinSound;

    int coins;
    int hp;
    int keys;
    bool *keysPressed;

    int startX;
    int startY;

    char destination;
    bool isLocationChanged;

    Player(void);
    Player(int i, int j, Cube ***map);
    ~Player(void);
    void collect(char type); //m-moneta, k-klucz
    bool openDoor();//sprawdza czy gracz ma wystarczajaca ilosc kluczy, zeby otworzyc drzwi - jak tak keys--
    bool allCollected();
    bool isDead();
    bool isFinished;
    friend ostream & operator<< (ostream &output, const Player &p);
    String state();
    Player & operator--();
    void virtual run();
    void setKeys(bool *keysPressed);
    void setDestination(char c);
    char getDestination();
    bool getIsLocationChanged();
    void setIsLocationChanged(bool b);
    bool getIsFinished();
};


#endif //PROJEKTSO_PLAYER_H
