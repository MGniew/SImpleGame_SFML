
#ifndef PROJEKTSO_MAZE_H
#define PROJEKTSO_MAZE_H
#include "Top.h"
#include <stdio.h>
#include <iostream>

class Maze
{

public:
    Top tops[10][10];
    bool readMaze(const char *stream);
    Maze(void);
    ~Maze(void);
};

#endif //PROJEKTSO_MAZE_H
