#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "unistd.h"
#include "battle_c.h"
#include "display.h"
#include "radar.h"

#define SPEED 5
#define DELAY 100000
#define FIRE_RATE 5
#define MAP_MIN_X 0
#define MAP_MAX_X 100
#define MAP_MIN_Y 0
#define MAP_MAX_Y 100

int main(int argc, char *argv[])
{
    BC_Connection *conn = bc_connect("5.135.136.236", 8080);

    BC_WorldInfo world_info = bc_get_world_info(conn);
    BC_PlayerData data = bc_get_player_data(conn);

    double angle = 0;
    int counter = 0;

    while (true) {
        data = bc_get_player_data(conn);

        angle = rand() % 360;

        double vx = cos(angle) * SPEED * 2;
        double vy = sin(angle * M_PI / 180) * SPEED * 2;

        if (data.position.x + vx < MAP_MIN_X || data.position.x + vx > MAP_MAX_X) {
            vx = -vx;
        }
        if (data.position.y + vy < MAP_MIN_Y || data.position.y + vy > MAP_MAX_Y) {
            vy = -vy;
        }

        bc_set_speed(conn, vx, vy, 0);

        if (counter % FIRE_RATE == 0) {
            double fire_angle = angle;
            bc_shoot(conn, fire_angle);
        }

        counter++;
        usleep(DELAY);
    }

    bc_disconnect(conn);
    return EXIT_SUCCESS;
}
