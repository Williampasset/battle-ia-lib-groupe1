#include "stdio.h"
#include "stdlib.h"
#include "battle_c.h"
#include "display.h"

int main(int argc, char *argv[])
{
  BC_Connection *conn = bc_connect("5.135.136.236", 8080);

  BC_WorldInfo world_info = bc_get_world_info(conn);

  BC_PlayerData data = bc_get_player_data(conn);

  BC_List *list = bc_radar_ping(conn);

  displayMapData(world_info);
  displayPlayerData(data);
  displayRadarData(list);
  
  // while(data.position.y > 0 && data.position.y < 100){
  //   data = bc_get_player_data(conn);
  //   bc_set_speed(conn, 0, -1, 0);

  //   bc_shoot(conn, 180);
  // }
  
  bc_disconnect(conn);

  return EXIT_SUCCESS;
}
