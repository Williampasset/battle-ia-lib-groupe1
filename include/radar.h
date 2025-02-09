#ifndef RADAR_H
#define RADAR_H

#include "utils.h"
#include "battle_c.h"

/*
    * Structure to store the radar data
    * @param players: the list of players
    * @param obstacles: the list of obstacles
    * @param bonuses: the list of bonuses
    * @param players_count: the number of players
    * @param obstacles_count: the number of obstacles
    * @param bonuses_count: the number of bonuses   
*/
typedef struct RadarData_ {
    BC_MapObject **players;
    BC_MapObject **obstacles;
    BC_MapObject **bonuses;
    int players_count;
    int obstacles_count;
    int bonuses_count;
} RadarData;

/*
    * Create a new radar data
    * @return: the new radar data   
*/
void update_radar_data(BC_Connection *conn, RadarData *radar_data);

/*
    * Print the radar data
    * @param radar_data: the radar data to print   
*/
void print_radar_data(RadarData *radar_data);

/*
    * Free the radar data
    * @param radar_data: the radar data to free   
*/
void free_radar_data(RadarData *radar_data);

/*
    * Sort the players by distance
    * @param robot_pos: the position of the robot
    * @param radar_data: the radar data to sort   
*/
void sort_players_by_distance(BC_Vector3 robot_pos, RadarData *radar_data);

/*
    * Sort bonuses by distance
    * @param robot_pos: the position of the robot
    * @param radar_data: the radar data to sort
    * @return: the closest bonus to the robot 
*/
void sort_bonuses_by_distance(BC_Vector3 robot_pos, RadarData *radar_data);

/*
    * Find the closest player to the robot
    * @param robot_pos: the position of the robot
    * @param radar_data: the radar data to search
    * @return: the closest player to the robot
*/
BC_MapObject *find_closest_boost(BC_Connection *conn, BC_Vector3 robot_pos);

/*
    * Move the robot towards the closest boost
    * @param conn: the connection to the server
    * @param robot_pos: the position of the robot
    * @param radar_data: the radar data to search
*/
void move_towards_closest_boost(BC_Connection *conn, BC_Vector3 robot_pos, RadarData *radar_data);

/*
    * Check if a position is blocked
    * @param pos: the position to check
    * @param radar_data: the radar data to check
    * @return: 1 if the position is blocked, 0 otherwise
*/
int is_position_blocked(BC_Vector3 pos, RadarData *radar_data);

#endif