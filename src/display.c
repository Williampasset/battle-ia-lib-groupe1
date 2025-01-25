#include "include/display.h"

void displayRadarData(BC_List *radarData)
{
    printf("Radar data: \n");
    do
    {
        BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(radarData);
        printf("map_object x = %d, y = %d\n", map_object->position.x,
               map_object->position.y);
        printf("map_object type = %d, id = %d, health = %d \n", map_object->type,
               map_object->id, map_object->health);

    } while (((radarData = bc_ll_next(radarData)) != NULL));
    printf('\n');
}

void displayMapData(BC_WorldInfo world_info)
{
    printf("map_x = %d, map_y = %d \n", (int)world_info.map_x, (int)world_info.map_y);
    printf("player_count = %d, auto_shoot_enabled = %d, radar_enabled = %d \n",
           (int)world_info.player_count, world_info.auto_shoot_enabled,
           world_info.radar_enabled);
    printf('\n');
}

void displayPlayerData(BC_PlayerData data){
    printf("Player Data: \n");
    printf("id = %d, position = (%d, %d, %d), speed = (%d, %d, %d), health = %d, score = %d, armor = %d, is_dead = %d \n",
           data.id, data.position.x, data.position.y, data.position.z, data.speed.x, data.speed.y, data.speed.z,
           data.health, data.score, data.armor, data.is_dead);
    printf('\n');
}