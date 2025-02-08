#include <stdio.h>
#include <stdlib.h>
#include "battle_c.h"

// typedef struct RadarObject {
//     double x, y;
//     double speed_x, speed_y;
//     int type, id, health;
//     struct RadarObject *next;
// } RadarObject;

typedef struct PlayerDataObject {
    double position_x, position_y;
    double speed_x, speed_y;
    int id, health, score, armor;
    bool is_shootable = true;
}

RadarObject
