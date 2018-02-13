#include "Top.h"

Top::Top(void)
{
}


Top::~Top(void)
{
}

void Top::setID(char c) {
    ID=c;
}

void Top::setNeighbours(char N, char W, char S, char E)
{
    neighbours[0]=N;
    neighbours[1]=W;
    neighbours[2]=S;
    neighbours[3]=E;
}


char Top::getID()
{
    return ID;
}

char Top::getNeighbour(int a)
{
    switch(a)
    {
        case 0: return neighbours[0];
        case 1: return neighbours[1];
        case 2: return neighbours[2];
        case 3: return neighbours[3];
        default: return 0;
    }
}