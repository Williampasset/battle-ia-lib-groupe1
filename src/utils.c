#include "utils.h"

double calculate_distance(BC_Vector3 pos1, BC_Vector3 pos2) {
    return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
}

double calculate_angle(BC_Vector3 pos1, BC_Vector3 pos2) {
    return atan2(pos2.y - pos1.y, pos2.x - pos1.x);
}