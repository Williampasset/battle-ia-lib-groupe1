#include "battle_c.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdbool.h"
#include <math.h>

/*
    * Calculate the distance between two points
    * @param pos1: the first position
    * @param pos2: the second position
    * @return: the distance between the two points
*/
double calculate_distance(BC_Vector3 pos1, BC_Vector3 pos2);

/*
    * Calculate the angle between two points
    * @param pos1: the first position
    * @param pos2: the second position
    * @return: the angle between the two points
*/
double calculate_angle(BC_Vector3 pos1, BC_Vector3 pos2);