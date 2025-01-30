#include <stdio.h>
#include <stdlib.h>
#include "battle_c.h"

typedef struct RadarObject {
    double x, y;
    double speed_x, speed_y;
    int type, id, health;
    struct RadarObject *next;
} RadarObject;

RadarObject *addRadarObject(RadarObject *head, BC_MapObject *map_object);
RadarObject *displayAndStoreRadarData(BC_List *radarData);
void freeRadarObjects(RadarObject **head);