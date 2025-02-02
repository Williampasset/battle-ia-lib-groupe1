#include "shoot.h"

bool is_shootable(BC_Vector3 robot_pos, BC_Vector3 enemy_pos, RadarData *radar_data) {
    double distance = calculate_distance(robot_pos, enemy_pos);
    double angle = calculate_angle(robot_pos, enemy_pos);

    for (int i = 0; i < radar_data->obstacles_count; i++) {
        BC_MapObject *obstacle = radar_data->obstacles[i];
        double obstacle_distance = calculate_distance(robot_pos, obstacle->position);
        double obstacle_angle = calculate_angle(robot_pos, obstacle->position);

        if (obstacle_distance < distance && fabs(obstacle_angle - angle) < 0.1) {
            return false;
        }
    }

    return true;
}