#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "unistd.h"
#include "battle_c.h"
#include "display.h"

#define SPEED 5
#define DELAY 100000
#define FIRE_RATE 5

int main(int argc, char *argv[])
{
    BC_Connection *conn = bc_connect("5.135.136.236", 8080);

    BC_WorldInfo world_info = bc_get_world_info(conn);
    BC_PlayerData data = bc_get_player_data(conn);

    double angle = 0;
    int counter = 0;
    int direction = 1;

    while (true) {
        data = bc_get_player_data(conn);

        if (data.position.x <= 20) {
            direction = 1; 
            angle = 0;
        } else if (data.position.x >= 80) {
            direction = -1;
            angle = 0;      
        }

        double vx = cos(angle / 10);
        double vy = direction * SPEED * sin(angle / 10);

        bc_set_speed(conn, 1, vy, 0);

        angle += 1;

        if (counter % FIRE_RATE == 0) {
            double fire_angle = angle * 180 / (M_PI * 10);
            bc_shoot(conn, fire_angle);
        }

        counter++;
        usleep(DELAY);
    }

    bc_disconnect(conn);
    return EXIT_SUCCESS;
}
