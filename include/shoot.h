#ifndef SHOOT_H
#define SHOOT_H

#include "radar.h"
#include "utils.h"

bool is_shootable(BC_Vector3 robot_pos, BC_Vector3 enemy_pos, RadarData *radar_data);

#endif