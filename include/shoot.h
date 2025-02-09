#ifndef SHOOT_H
#define SHOOT_H

#include "radar.h"
#include "utils.h"

/*
    * Is the enemy shootable
    * @param robot_pos: the position of the robot
    * @param enemy_pos: the position of the enemy
    * @param radar_data: the radar data
    * @return: true if the enemy is shootable, false otherwise
*/
bool is_shootable(BC_Vector3 robot_pos, BC_Vector3 enemy_pos, RadarData *radar_data);

#endif