#include "stdio.h"
#include "stdlib.h"
<<<<<<< HEAD
#include "battle_c.h"
#include "display.h"


=======
#include "header/display.h"
>>>>>>> 1416786 (add display files)

int main(int argc, char *argv[]) {

  BC_Connection *conn = bc_connect("5.135.136.236", 8080);

  BC_WorldInfo world_info = bc_get_world_info(conn);

  bc_set_speed(conn, 1.2, 0.4, 0);

  BC_PlayerData data = bc_get_player_data(conn);

  BC_List *list = bc_radar_ping(conn);

  printf("map_x = %d, map_y = %d \n", (int)world_info.map_x, (int)world_info.map_y);
  printf("player_count = %d, auto_shoot_enabled = %d, radar_enabled = %d \n",
         (int)world_info.player_count, world_info.auto_shoot_enabled,
         world_info.radar_enabled);

<<<<<<< HEAD
  // displayMapDataObjects(list);

  displayMap(list, world_info);
=======

  displayMap(list);
  bc_disconnect(conn);
>>>>>>> 1416786 (add display files)

  return EXIT_SUCCESS;
}
