#include "Maze.h"

Maze::Maze(void)
{
}


Maze::~Maze(void)
{
}

bool Maze::readMaze(const char *stream) {

    FILE *file;
    char N,W,E,S;

    if ((file = fopen(stream,"rt") ) != NULL )
    {
        char c;
        for(int i=0;i<10;i++) {
            for(int j=0;j<10;j++) {
                do {
                    c= (char) fgetc(file);
                }
                while ((c==10 || c==13));
                tops[i][j].setID(c);
            }
        }

        for(int i=0;i<10;i++)
            for (int j=0;j<10;j++) {
                if (i>0) N=tops[i-1][j].getID(); else N='0';
                if  (j>0) W=tops[i][j-1].getID(); else W='0';
                if (j<9) E=tops[i][j+1].getID(); else E='0';
                if (i<9) S=tops[i+1][j].getID(); else S='0';
                tops[i][j].setNeighbours(N, W, S, E);
            }
        fclose(file);
        return true;
    }

    else return false;


}