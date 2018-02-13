#ifndef PROJEKTSO_TOP_H
#define PROJEKTSO_TOP_H


class Top
{

public:
    char ID;
    char neighbours[4];
    void setID(char c);
    void setNeighbours(char N, char W, char S, char E);
    Top(void);
    ~Top(void);
    char getID();
    char getNeighbour(int a);
};



#endif //PROJEKTSO_TOP_H
