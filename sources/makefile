CC = g++

all: Door.o Ghost.o Eye.o Ogr.o Enemy.o Player.o MovableObject.o Cube.o Engine.o Game.o Location.o Maze.o main.o Top.o
	$(CC) Door.o Ghost.o Eye.o Ogr.o Enemy.o Player.o MovableObject.o Cube.o Engine.o Game.o Location.o Maze.o main.o Top.o -o YouShallNotPass -I/usr/local/include/SFML -L/usr/local/lib  -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -lpthread -std=c++11
Ghost.o:
	$(CC) Ghost.cpp -c -o Ghost.o -std=c++11
Cube.o:
	$(CC) Cube.cpp -c -o Cube.o -std=c++11
Door.o:
	$(CC) Door.cpp -c -o Door.o -std=c++11
Enemy.o:
	$(CC) Enemy.cpp -c -o Enemy.o -std=c++11
Engine.o:
	$(CC) Engine.cpp -c -o Engine.o -std=c++11
Location.o:
	$(CC) Location.cpp -c -o Location.o -std=c++11
Maze.o:
	$(CC) Maze.cpp -c -o Maze.o -std=c++11
MovableObject.o:
	$(CC) MovableObject.cpp -c -o MovableObject.o -std=c++11
Ogr.o:
	$(CC) Ogr.cpp -c -o Ogr.o -std=c++11
Eye.o:
	$(CC) Eye.cpp -c -o Eye.o -std=c++11
Player.o:
	$(CC) Player.cpp -c -o Player.o -std=c++11
main.o:
	$(CC)  main.cpp -c -o main.o -std=c++11
Top.o:
	$(CC) Top.cpp -c -o Top.o -std=c++11
Game.o:
	$(CC) Game.cpp -c -o Game.o -std=c++11
clean:
	rm -f *.o test
