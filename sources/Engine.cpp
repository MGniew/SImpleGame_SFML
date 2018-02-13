#include "Engine.h"

Engine::Engine(sf::RenderWindow &win) {

    if (music.openFromFile("FontImages/music.wav")) {
        music.setVolume(20);
        music.setLoop(true);
        music.play();
    }

    if (doorSoundBuffer.loadFromFile("FontImages/door.wav")) {
        doorSound.setVolume(65);
        doorSound.setBuffer(doorSoundBuffer);
    }
    font.loadFromFile("FontImages/GoodDog.otf");

    maze.readMaze("Stages/Stage1/maze.txt");
    for (int i=0;i<10;i++)
        for (int j=0;j<10;j++)
            if (maze.tops[i][j].getID()=='1')
            {
                xCurrTop=i;
                yCurrTop=j;
            }
    player = NULL;
    location = NULL;
    setMap("Stages/Stage1/1.txt");


    winner=false;
    exitToMenu=false;
    run(win);
}

Engine::~Engine(void) {

    destroyLocation();
    remove("Stages/Stage1/temp1.txt");
    remove("Stages/Stage1/temp2.txt");
    remove("Stages/Stage1/temp3.txt");
    remove("Stages/Stage1/temp4.txt");
    remove("Stages/Stage1/temp5.txt");
    remove("Stages/Stage1/temp6.txt");
    remove("Stages/Stage1/temp7.txt");
    remove("Stages/Stage1/temp8.txt");
}

void Engine::setMap(const char *a) {

    destroyLocation();
    location = new Location;
    location->readLocation(a);
    m.lock();
    for (int i=0;i<location->HEIGHT;i++) {
        for (int j=0;j<location->WIDTH;j++) {
            if (location->map[i][j] != NULL)
                switch(location->map[i][j]->type) {

                    case 'p': {
                        dynamic_cast<Player*>(location->map[i][j])->start(&m);
                        dynamic_cast<Player*>(location->map[i][j])->setPosition(location->cube_width,location->cube_height);
                        dynamic_cast<Player*>(location->map[i][j])->setKeys(keysPressed);
                        player = dynamic_cast<Player*>(location->map[i][j]);
                    } break;
                    case ' ': break;

                    case '1': { //zrób enemy debilu
                        dynamic_cast<Ogr*>(location->map[i][j])->start(&m);
                        dynamic_cast<Ogr*>(location->map[i][j])->setPosition(location->cube_width,location->cube_height);
                    } break;

                    case '2': {
                        dynamic_cast<Eye*>(location->map[i][j])->start(&m);
                        dynamic_cast<Eye*>(location->map[i][j])->setPosition(location->cube_width,location->cube_height);
                    } break;

                    case '3': {
                        dynamic_cast<Ghost*>(location->map[i][j])->start(&m);
                        dynamic_cast<Ghost*>(location->map[i][j])->setPosition(location->cube_width,location->cube_height);
                    } break;

                    case 'd': {
                        if (j == 31) {
                            dynamic_cast<Door*>(location->map[i][j])->
                                    setDestination(maze.tops[xCurrTop][yCurrTop].getNeighbour(3));
                        }
                        else if (i == 0) {
                            dynamic_cast<Door*>(location->map[i][j])->
                                    setDestination(maze.tops[xCurrTop][yCurrTop].getNeighbour(0));
                        }
                        else if (j == 0) {
                            dynamic_cast<Door*>(location->map[i][j])->
                                    setDestination(maze.tops[xCurrTop][yCurrTop].getNeighbour(1));
                        }
                        else if (i == 17) {
                            dynamic_cast<Door*>(location->map[i][j])->
                                    setDestination(maze.tops[xCurrTop][yCurrTop].getNeighbour(2));
                        }
                        location->map[i][j]->setPosition(location->cube_width,location->cube_height);
                    } break;

                    default: location->map[i][j]->setPosition(location->cube_width,location->cube_height);


                }
        }
    }
    m.unlock();


}

void Engine::run(sf::RenderWindow &window) {

    Event event;
    chrono::system_clock::time_point start;
    chrono::system_clock::time_point stop;
    chrono::duration<double, std::milli> loopTime;

    Text text;
    text.setFont(font);
    text.setStyle(Text::Bold);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition(40,17*40);

    while(!exitToMenu) {
        start = chrono::system_clock::now();


        while(window.pollEvent(event)) {
            if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
                exitToMenu = true;

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up)
                keysPressed[0] = true;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
                keysPressed[1] = true;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
                keysPressed[2] = true;
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
                keysPressed[3] = true;
        }

        window.clear(sf::Color(120,120,120));
        for (int i=0;i<location->HEIGHT;i++)
            for(int j=0;j<location->WIDTH;j++)
                if (location->map[i][j] != NULL)
                    window.draw(location->map[i][j]->sprite);
        text.setString(player->state());
        window.draw(text);
        window.display();


        stop = chrono::system_clock::now();
        loopTime = stop - start;
        if (20 - loopTime.count() > 0)
            this_thread::sleep_for(chrono::milliseconds(20 - (int)loopTime.count()));

        if (player->getIsLocationChanged()) {
            loadLocation();
        }

        if (player->isDead()) {
            exitToMenu = true;
            showText(window, sf::Color::Black, "GAME OVER", sf::Color::Red, 2000);
        }

        if (player->isFinished) {
            exitToMenu = true;
            showText(window, sf::Color::Blue, "YOU WON", sf::Color::Yellow, 2000);
        }
    }
}

void Engine::destroyLocation() {

    player = NULL;
    m.lock();
    delete location;
    m.unlock();
    location = NULL;
}

void Engine::loadLocation() {

    string temp = "temp";
    temp = temp + maze.tops[xCurrTop][yCurrTop].getID() + ".txt";
    m.lock();
    saveMap(temp);
    m.unlock();
    int keys = player->keys;
    int hp = player->hp;
    int coins = player->coins;
    int playerX = player->x;
    int playerY = player->y;

    if (player->getDestination() == maze.tops[xCurrTop][yCurrTop].getNeighbour(0)) {
        xCurrTop--;
        playerX = Location::HEIGHT-2;
    } else if (player->getDestination() == maze.tops[xCurrTop][yCurrTop].getNeighbour(1)){
        yCurrTop--;
        playerY = Location::WIDTH-2;
    } else if  (player->getDestination() == maze.tops[xCurrTop][yCurrTop].getNeighbour(2)){
        xCurrTop++;
        playerX = 1;
    } else {
        yCurrTop++;
        playerY = 1;
    }
    string stage = "Stages/Stage1/";

        if(fileExists((stage + "temp" + player->getDestination() + ".txt").c_str()))
            setMap((stage + "temp" + player->getDestination() + ".txt").c_str());
        else
            setMap((stage + player->getDestination() + ".txt").c_str());

    m.lock();
        if (player == NULL) {
            player = new Player(playerX, playerY, location->map);
            player->setKeys(keysPressed);
            player->start(&m);
        }
        location->map[player->x][player->y]=NULL;
        location->map[playerX][playerY] = player;
        player->x = playerX;
        player->y = playerY;
        player->startX= playerX;
        player->startY = playerY;
        player->hp = hp;
        player->coins = coins;
        player->keys = keys;
    m.unlock();
    player->setPosition(location->cube_width,location->cube_height);
}

void Engine::showText(sf::RenderWindow &window, sf::Color clearColor, const char *a, sf::Color textColor, int time) {

    window.clear(clearColor);
    sf::Text text;
    text.setString(a);
    text.setFont(font);
    text.setStyle(Text::Bold);
    text.setCharacterSize(200);
    text.setFillColor(textColor);

    text.setPosition(1280/2-text.getGlobalBounds().width/2,720/2-text.getGlobalBounds().height);
    window.draw(text);
    window.display();
    this_thread::sleep_for(chrono::milliseconds(time));
}

bool Engine::fileExists(const char* fileName)
{
    FILE* file;
    file = fopen( fileName,"r");
    if( file == NULL)
        return false;
    else {
        fclose(file);
        return true;
    }
}

bool Engine::saveMap(string fileName) {

    FILE *file;

    fileName = "Stages/Stage1/" + fileName;
    file=fopen(fileName.c_str(),"wt");
    for (int i=0;i<location->HEIGHT;i++) {
        fprintf(file,"\n");
        for (int j=0;j<location->WIDTH;j++) {
            if (location->map[i][j] == NULL) {
                fprintf(file, " ");
            }
            else if (location->map[i][j] -> type == 'd') {
                if (dynamic_cast<Door*>(location->map[i][j])->isOpen)
                    fprintf(file, "o");
                else
                    fprintf(file, "c");
            }
            else
                fprintf(file, "%c", location->map[i][j]->type);
        }
    }
    fclose(file);
}


