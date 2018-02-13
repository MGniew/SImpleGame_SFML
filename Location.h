#ifndef PROJEKTSO_LOCATION_H
#define PROJEKTSO_LOCATION_H
#include "Top.h"
#include "Cube.h"
#include "Ogr.h"
#include "Eye.h"
#include "Ghost.h"
#include "Door.h"
#include <stdio.h>
#include <iostream>
#include "Player.h"

class Location : public Top {

    public:
        Location(void);
        ~Location(void);
        void readLocation(const char *stream);

        const static int WIDTH=32, HEIGHT=18;
        const static int cube_width=40;
        const static int cube_height=40;
        Cube*** map;
};

#endif //PROJEKTSO_LOCATION_H
