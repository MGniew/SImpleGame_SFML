#include "Game.h"

RenderWindow window(VideoMode(1280,720),"You shall not pass",Style::Default);

Game::Game() {

    if(!font.loadFromFile("FontImages/GoodDog.otf")) {
        return;
    }
    status=MENU;
    window.setKeyRepeatEnabled(false);
}

Game::~Game() {
}

void Game::Run()
{
    while (status!=END) {
        switch (status) {
            case MENU:
                MainMenu(); break;
            case PLAYING:
                Play(); break;
            case END: break;
        }
    }
}

void Game::MainMenu()

{
    Event event;
    Text title("You shall not pass",font,80);
    title.setStyle(Text::Bold);
    title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

    const int ile=2;
    Text a[ile];

    string str[] = {"Graj","Koniec"};
    for (int i=0;i<ile;i++)
    {
        a[i].setFont(font);
        a[i].setCharacterSize(65);
        a[i].setString(str[i]);
        a[i].setPosition(1280/2-a[i].getGlobalBounds().width/2,250+i*120);
    }

    while(status == MENU)
    {
        Vector2f mouse(Mouse::getPosition(window));


        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed || event.type == Event::KeyPressed &&
                                              event.key.code == Keyboard::Escape)
                status = END;

            else if(a[1].getGlobalBounds().contains(mouse) &&
                    event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                status = END;
            }

            else if(a[0].getGlobalBounds().contains(mouse) &&
                    event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
            {
                status = PLAYING;
            }

        }
        for(int i=0;i<ile;i++)
            if(a[i].getGlobalBounds().contains(mouse))
                a[i].setFillColor(Color::Red);
            else a[i].setFillColor(Color::White);

        window.clear();

        window.draw(title);
        for(int i=0;i<ile;i++)
            window.draw(a[i]);

        window.display();
    }
}

void Game::Play()
{
    Engine a(window);
    a.run(window);
    status=MENU;
}
