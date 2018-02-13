#include "Player.h"

Player::Player(void) {


    if(!texture.loadFromFile("FontImages/postac.png"))
    {
        printf("postac.png");
        return;
    }

    if (moveSoundBuffer.loadFromFile("FontImages/steps.wav")) {
        moveSound.setVolume(65);
        moveSound.setBuffer(moveSoundBuffer);
    }

    if(dieSoundBuffer.loadFromFile("FontImages/die.wav")) {
        dieSound.setVolume(80);
        dieSound.setBuffer(dieSoundBuffer);
    }

    if (coinSoundBuffer.loadFromFile("FontImages/coin.wav")) {
        coinSound.setVolume(65);
        coinSound.setBuffer(coinSoundBuffer);
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0,0,30,39));
    sprite.setPosition(0,0);
    sprite.setOrigin(0,0);

    keys=0;
    hp=5;
    coins=0;
    x=0;
    y=0;
    type='p';
    isLocationChanged = false;
    isFinished = false;
}

Player::~Player(void) {
}

void Player::collect(char type) {
    if (type=='k') keys++;
    if (type=='m') coins++;
}

bool Player::openDoor() {

    if (keys>0) {
        keys--;
        return true;
    }
    else
        return false;
}

bool Player::allCollected() {
    return coins == 25;
}

bool Player::isDead() {
    return hp < 0;
}

void Player::run() {

    int xi, yi;
    char a;
    while (!threadStop) {

        xi = 0;
        yi = 0;

        if (keysPressed[0])
            xi = -1;
        else if (keysPressed[1])
            yi = -1;
        else if (keysPressed[2])
            xi = 1;
        else if (keysPressed[3])
            yi = 1;

        for(int i = 0; i < 4; i++)
            keysPressed[i]=false;

        if (mutex->try_lock()) {
            if (map[x + xi][y + yi] == NULL) {
                map[x + xi][y + yi] = map[x][y];
                map[x][y] = NULL;
                y += yi;
                x += xi;
            } else {
                    switch (map[x + xi][y + yi]->type) {
                        case 'm': case 'k': {
                            a = map[x + xi][y + yi]->type;
                            delete map[x + xi][y + yi];
                            map[x + xi][y + yi] = map[x][y];
                            map[x][y] = NULL;
                            collect(a);
                            coinSound.play();
                            y += yi;
                            x += xi;
                        } break;
                        case '1': case '2': case '3': {
                            this->operator--();
                        } break;
                        case 'd': {
                            if (dynamic_cast<Door*>(map[x + xi][y + yi])->isOpen) {
                                destination = dynamic_cast<Door*>(map[x + xi][y + yi])->getDestination();
                                isLocationChanged = true;
                            } else {
                                if (openDoor()) {
                                    dynamic_cast<Door *>(map[x + xi][y + yi])->open();
                                }
                            }
                        } break;
                        case 'e': {
                            isFinished = true;
                        } break;
                        default: break;
                    }
                }
            setPosition(Location::cube_width, Location::cube_height);
            mutex->unlock();
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
}

ostream &operator<<(ostream &output, const Player &p) {
    output <<"HP: "<< p.hp << " KEYS: " << p.keys << " POINTS: " << p.coins << endl;
    return output;
}

Player &Player::operator--() {
    map[startX][startY] = map[x][y];
    map[x][y] = NULL;
    x = startX;
    y = startY;
    dieSound.play();
    hp--;
    return *this;
}

Player::Player(int i, int j, Cube ***map) : Player() {
    x = i;
    y = j;
    startX = i;
    startY = j;
    this->map=map;

}

void Player::setKeys(bool* keysPressed){
    this->keysPressed = keysPressed;
}

String Player::state() {
    return "HP: " + to_string(hp) + "   KEYS: " + to_string(keys) + "   COINS: " + to_string(coins);
}

void Player::setDestination(char c) {
    destination = c;
}

char Player::getDestination() {
    return destination;
}

bool Player::getIsLocationChanged() {
    return isLocationChanged;
}

void Player::setIsLocationChanged(bool b) {
    isLocationChanged = b;
}

bool Player::getIsFinished() {
    return isFinished;
}

