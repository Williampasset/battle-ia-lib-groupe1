<<<<<<< HEAD
#include "include/display.h"

void displayMap(BC_List *mapObjects, BC_WorldInfo world_info) {
  // Display the map
  printf("Map:\n");
  for(int i = 0; i<world_info.map_x; i++){
      for(int j = 0; j<world_info.map_y; j++){
          if(mapObjects != NULL){
              BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(mapObjects);
              if(map_object->position.x == i && map_object->position.y == j){
                  printf("X");
                  mapObjects = bc_ll_next(mapObjects);
              } else {
                printf(".");
              }
          } else {
              printf(".");
          }
      }
      printf("\n");
  }   
=======
#include "header/display.h"

void displayMapDataObjects(BC_List *mapObjects) {
    // Display the map data
    printf("Map:\n");
    do {
        BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(mapObjects);
        printf("map_object x = %d, y = %d \n", map_object->position.x,
            map_object->position.y);
        printf("speed x = %d, y = %d \n", map_object->speed.x,
            map_object->speed.y);
        printf("type = %d, id = %d \n", (int)map_object->type,
            map_object->id);
        printf("health = %d \n", map_object->health);
        printf("\n");

    } while (((mapObjects = bc_ll_next(mapObjects)) != NULL));
>>>>>>> 1416786 (add display files)
}

void displayMap(BC_List *mapObjects){
    // Display the map
    printf("Map:\n");
    
}