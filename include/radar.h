#ifndef RADAR_H
#define RADAR_H

#include "utils.h"
#include "battle_c.h"

typedef struct RadarData_ {
    BC_MapObject **players;
    BC_MapObject **obstacles;
    BC_MapObject **bonuses;
    int players_count;
    int obstacles_count;
    int bonuses_count;
} RadarData;

void update_radar_data(BC_Connection *conn, RadarData *radar_data);
void print_radar_data(RadarData *radar_data);
void free_radar_data(RadarData *radar_data);

void sort_players_by_distance(BC_Vector3 robot_pos, RadarData *radar_data);
void sort_bonuses_by_distance(BC_Vector3 robot_pos, RadarData *radar_data);
BC_MapObject *find_closest_boost(BC_Connection *conn, BC_Vector3 robot_pos);
void move_towards_closest_boost(BC_Connection *conn, BC_Vector3 robot_pos, RadarData *radar_data);
int is_position_blocked(BC_Vector3 pos, RadarData *radar_data);

#endif