#include "stdio.h"
#include "stdlib.h"
#include "include/display.h"

// void displayMapDataObjects(BC_List *mapObjects) {
//     // Display the map data
//     printf("Map:\n");
//     do {
//         BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(mapObjects);
//         printf("map_object x = %d, y = %d \n", map_object->position.x,
//             map_object->position.y);
//         printf("speed x = %d, y = %d \n", map_object->speed.x,
//             map_object->speed.y);
//         printf("type = %d, id = %d \n", (int)map_object->type,
//             map_object->id);
//         printf("health = %d \n", map_object->health);
//         printf("\n");

//     } while (((mapObjects = bc_ll_next(mapObjects)) != NULL));
// }

// void displayMap(BC_List *mapObjects, BC_WorldInfo world_info) {
//   // Display the map
//   printf("Map:\n");
//   for(int i = 0; i<world_info.map_x; i++){
//       for(int j = 0; j<world_info.map_y; j++){
//           if(mapObjects != NULL){
//               BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(mapObjects);
//               if(map_object->position.x == i && map_object->position.y == j){
//                   printf("X");
//                   mapObjects = bc_ll_next(mapObjects);
//               } else {
//                 printf(".");
//               }
//           } else {
//               printf(".");
//           }
//       }
//       printf("\n");
//   }   
// }

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

  // displayMapDataObjects(list);

  return EXIT_SUCCESS;
}
