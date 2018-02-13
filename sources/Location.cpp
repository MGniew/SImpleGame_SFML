#include "Location.h"


Location::Location(void)
{
    map = new Cube**[HEIGHT];
    for (int i =0;i<HEIGHT;i++) {
        map[i] = new Cube*[WIDTH];
    }
}


Location::~Location(void)
{
    for(int i=0;i<HEIGHT;i++)
        for(int j=0;j<WIDTH;j++) {
            if (map[i][j]!=NULL)
                delete map[i][j];
            map[i][j] = NULL;
        }

    for (int i = 0; i < HEIGHT; i++) {
        delete[] map[i];
    }
    delete[] map;
}

void Location::readLocation(const char* stream)
{
    FILE *file;
    bool playerSet = false;
    if ((file = fopen(stream,"r") ) != NULL ) {

        char c;
        for(int i=0;i<HEIGHT;i++) {
            for(int j=0;j<WIDTH;j++) {

                do {
                    c = (char) fgetc(file);
                }
                while ((c==10 || c==13));
                switch(c) {
                    case ' ' : map[i][j] = NULL; break;
                    case 'p' :
                        if (playerSet) {
                            map[i][j] = NULL;
                        }
                        else {
                            map[i][j] = new Player(i,j, map);
                            playerSet = true;
                        } break;
                    case '1' : map[i][j] = new Ogr(i,j, map); break;
                    case '2' : map[i][j] = new Eye(i,j, map); break;
                    case '3' : map[i][j] = new Ghost(i,j, map); break;
                    case 'c' : map[i][j] = new Door(i, j, false); break;
                    case 'o' : map[i][j] = new Door(i, j, true); break;
                    default:  map[i][j] = new Cube(i,j,c); break;
                    }

            }
        }
    }
    fclose(file);
}

