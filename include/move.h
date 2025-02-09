#include "utils.h"
#include "battle_c.h"
#define SPEED 10

/*
    * Move the bot to the target position
    * @param conn: the connection to the server
    * @param player_pos: the current position of the bot
    * @param target_pos: the target position of the bot
*/
void move_bot(BC_Connection *conn, BC_Vector3 player_pos, BC_Vector3 target_pos);