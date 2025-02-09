#include "radar.h"
#include <float.h>
#include <math.h>
#define SPEED 1.0


void update_radar_data(BC_Connection *conn, RadarData *radar_data) {
    BC_List *list = bc_radar_ping(conn);

    radar_data->players_count = 0;
    radar_data->obstacles_count = 0;
    radar_data->bonuses_count = 0;

    while (list) {
        BC_MapObject *obj = (BC_MapObject *)bc_ll_value(list);
        
        switch (obj->type) {

            //Pour les joueurs
            case 0:
                radar_data->players = realloc(radar_data->players, (radar_data->players_count + 1) * sizeof(BC_MapObject *));
                radar_data->players[radar_data->players_count++] = obj;
                break;

            //Pour les obstacles
            case 1:
                if(obj->position.x == 1 || obj->position.x == 99 || obj->position.y == 1 || obj->position.y == 99)
                    break;
                radar_data->obstacles = realloc(radar_data->obstacles, (radar_data->obstacles_count + 1) * sizeof(BC_MapObject *));
                radar_data->obstacles[radar_data->obstacles_count++] = obj;
                break;

            //Pour les bonus
            case 2:
                radar_data->bonuses = realloc(radar_data->bonuses, (radar_data->bonuses_count + 1) * sizeof(BC_MapObject *));
                radar_data->bonuses[radar_data->bonuses_count++] = obj;
                break;
        }
        list = bc_ll_next(list);
    }
}


void print_radar_data(RadarData *radar_data) {
    printf("Players:\n");
    for (int i = 0; i < radar_data->players_count; i++) {
        BC_MapObject *obj = radar_data->players[i];
        printf("Player %d: (%f, %f, %f)\n", obj->id, obj->position.x, obj->position.y, obj->position.z);
        printf("Player %d: (%f, %f, %f)\n", obj->id, obj->speed.x, obj->speed.y, obj->speed.z);
        printf("Player %d: %d\n", obj->id, obj->health);
    }

    // printf("Obstacles:\n");
    // for (int i = 0; i < radar_data->obstacles_count; i++) {
    //     BC_MapObject *obj = radar_data->obstacles[i];
    //     printf("Obstacle %d: (%f, %f, %f)\n", obj->id, obj->position.x, obj->position.y, obj->position.z);
    // }

    printf("Bonuses:\n");
    for (int i = 0; i < radar_data->bonuses_count; i++) {
        BC_MapObject *obj = radar_data->bonuses[i];
        printf("Bonus %d: (%f, %f, %f)\n", obj->id, obj->position.x, obj->position.y, obj->position.z);
    }
}

void free_radar_data(RadarData *radar_data) {
    free(radar_data->players);
    free(radar_data->obstacles);
    free(radar_data->bonuses);
    radar_data->players = NULL;
    radar_data->obstacles = NULL;
    radar_data->bonuses = NULL;
    radar_data->players_count = 0;
    radar_data->obstacles_count = 0;
    radar_data->bonuses_count = 0;
}

void sort_players_by_distance(BC_Vector3 robot_pos, RadarData *radar_data) {
    for (int i = 0; i < radar_data->players_count; i++) {
        for (int j = i + 1; j < radar_data->players_count; j++) {
            double distance1 = calculate_distance(robot_pos, radar_data->players[i]->position);
            double distance2 = calculate_distance(robot_pos, radar_data->players[j]->position);

            if (distance1 > distance2) {
                BC_MapObject *tmp = radar_data->players[i];
                radar_data->players[i] = radar_data->players[j];
                radar_data->players[j] = tmp;
            }
        }
    }
}

void sort_bonuses_by_distance(BC_Vector3 robot_pos, RadarData *radar_data){
    for (int i = 0; i < radar_data->bonuses_count; i++) {
        for (int j = i + 1; j < radar_data->bonuses_count; j++) {
            double distance1 = calculate_distance(robot_pos, radar_data->bonuses[i]->position);
            double distance2 = calculate_distance(robot_pos, radar_data->bonuses[j]->position);

            if (distance1 > distance2) {
                BC_MapObject *tmp = radar_data->bonuses[i];
                radar_data->bonuses[i] = radar_data->bonuses[j];
                radar_data->bonuses[j] = tmp;
            }
        }
    }
}

BC_MapObject *find_closest_boost(BC_Connection *conn, BC_Vector3 robot_pos) {
    BC_List *list = bc_radar_ping(conn);
    if (!list) {
        return NULL;
    }

    BC_MapObject *closest_boost = NULL;
    double min_distance = DBL_MAX;

    while (list) {
        BC_MapObject *obj = (BC_MapObject *)bc_ll_value(list);
        if (obj->type == 2) { // Type 2 corresponds to bonuses
            double distance = calculate_distance(robot_pos, obj->position);
            if (distance < min_distance) {
                min_distance = distance;
                closest_boost = obj;
            }
        }
        list = bc_ll_next(list);
    }

    return closest_boost;
}

void move_towards_closest_boost(BC_Connection *conn, BC_Vector3 robot_pos) {
    BC_MapObject *closest_boost = find_closest_boost(conn, robot_pos);
    if (closest_boost != NULL) {
        printf("Closest boost found at: (%f, %f, %f)\n", closest_boost->position.x, closest_boost->position.y, closest_boost->position.z);
        
        // Calculer l'angle vers le boost le plus proche
        double dx = closest_boost->position.x - robot_pos.x;
        double dy = closest_boost->position.y - robot_pos.y;
        double angle_to_boost = atan2(dy, dx) * 180 / M_PI;

        // Mettre à jour la vitesse pour se diriger vers le boost
        double vx = cos(angle_to_boost * M_PI / 180) * SPEED * 2;
        double vy = sin(angle_to_boost * M_PI / 180) * SPEED * 2;
        bc_set_speed(conn, vx, vy, 0);
    } else {
        // Si aucun boost n'est trouvé, continuer à se déplacer de manière aléatoire
        double angle = rand() % 360;
        double vx = cos(angle * M_PI / 180) * SPEED * 2;
        double vy = sin(angle * M_PI / 180) * SPEED * 2;
        bc_set_speed(conn, vx, vy, 0);
    }
}