#include "move.h"

void move_bot(BC_Connection *conn, BC_Vector3 player_pos, BC_Vector3 target_pos){
    double angle = calculate_angle(player_pos, target_pos);
    double vy = cos(angle * M_PI / 180) * SPEED;
    double vx = sin(angle * M_PI / 180) * SPEED;
    bc_set_speed(conn, vx, vy, 0);
}