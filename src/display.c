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
