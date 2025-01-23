#include "stdio.h"
#include "stdlib.h"
#include "battle_c.h"
#include "display.h"
#include <math.h> // Pour fabs (valeur absolue flottante)

int main(int argc, char *argv[])
{

  int i = 0;

  BC_Connection *conn = bc_connect("5.135.136.236", 8080);

  BC_WorldInfo world_info = bc_get_world_info(conn);

  BC_PlayerData data = bc_get_player_data(conn);

  BC_List *list = bc_radar_ping(conn);

  printf("map_x = %d, map_y = %d \n", (int)world_info.map_x, (int)world_info.map_y);
  printf("player_count = %d, auto_shoot_enabled = %d, radar_enabled = %d \n",
         (int)world_info.player_count, world_info.auto_shoot_enabled,
         world_info.radar_enabled);

  // if(i == 0){
  //   printf("Player Data: \n");
  //   printf("id = %d, position = (%d, %d, %d), speed = (%d, %d, %d), health = %d, score = %d, armor = %d, is_dead = %d \n",
  //          data.id, data.position.x, data.position.y, data.position.z, data.speed.x, data.speed.y, data.speed.z,
  //          data.health, data.score, data.armor, data.is_dead);
  //   i+=1;
  // }



  while (data.is_dead == false)
  {
    data = bc_get_player_data(conn);
    list = bc_radar_ping(conn);

    bc_set_speed(conn, 0, -0.6, 0.0);
  
    for(int i = 0; i<2; i++){
      bc_shoot(conn, 0);
      usleep(3000);
    }
  }
  bc_disconnect(conn);

  return EXIT_SUCCESS;
}
