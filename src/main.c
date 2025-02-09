#include "main.h"
#include "radar.h"
#include "unistd.h"
#include <time.h>
#include <math.h>
#include <float.h>
#include <pthread.h> // Pour les threads

#define SPEED 1.0
#define DELAY 300000

typedef struct {
    BC_Connection *conn;
    BC_PlayerData *data;
    RadarData *radar_data;
} ThreadArgs;

void *movement_thread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    BC_Connection *conn = thread_args->conn;
    BC_PlayerData *data = thread_args->data;
    RadarData *radar_data = thread_args->radar_data;

    while (!data->is_dead) {
        move_towards_closest_boost(conn, data->position, radar_data);
        usleep(DELAY);
    }

    return NULL;
}

void *shooting_thread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    BC_Connection *conn = thread_args->conn;
    BC_PlayerData *data = thread_args->data;
    RadarData *radar_data = thread_args->radar_data;

    while (!data->is_dead) {
        for (int i = 0; i < radar_data->players_count; i++) {
            BC_MapObject *player = radar_data->players[i];
            if (is_shootable(data->position, player->position, radar_data)) {
                double angle = calculate_angle(data->position, player->position);
                bc_shoot(conn, angle);
                break;
            }
        }
        usleep(DELAY);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    BC_Connection *conn = bc_connect("5.135.136.236", 8080);

    BC_WorldInfo world_info = bc_get_world_info(conn);

    bc_set_speed(conn, 0, 0, 0);

    BC_PlayerData data = bc_get_player_data(conn);

    RadarData radar_data = {NULL, NULL, NULL, 0, 0, 0};

    update_radar_data(conn, &radar_data);

    //print_radar_data(&radar_data);

    double angle = 0;
    int lastping = time(NULL);

    ThreadArgs thread_args = {conn, &data, &radar_data};

    pthread_t movement_tid, shooting_tid;
    pthread_create(&movement_tid, NULL, movement_thread, &thread_args);
    pthread_create(&shooting_tid, NULL, shooting_thread, &thread_args);

    while (!data.is_dead) {
        data = bc_get_player_data(conn);

        if (time(NULL) - lastping > 1) {
            lastping = time(NULL);
            update_radar_data(conn, &radar_data);
        }

        usleep(DELAY);
    }

    pthread_join(movement_tid, NULL);
    pthread_join(shooting_tid, NULL);

    bc_disconnect(conn);
    return EXIT_SUCCESS;
}