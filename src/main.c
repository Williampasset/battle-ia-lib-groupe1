#include "main.h"

int main(int argc, char *argv[])
{

    BC_Connection *conn = bc_connect("5.135.136.236", 8080);

    BC_WorldInfo world_info = bc_get_world_info(conn);

    bc_set_speed(conn, 0, 0, 0);

    BC_PlayerData data = bc_get_player_data(conn);

    RadarData radar_data = {NULL, NULL, NULL, 0, 0, 0};

    update_radar_data(conn, &radar_data);

    print_radar_data(&radar_data);

    while(!data.is_dead){
        data = bc_get_player_data(conn);
        update_radar_data(conn, &radar_data);

        sort_players_by_distance(data.position, &radar_data);

        for(int i = 0; i < radar_data.players_count; i++){
            BC_MapObject *player = radar_data.players[i];
            if(is_shootable(data.position, player->position, &radar_data)){
                double angle = calculate_angle(data.position, player->position);
                bc_shoot(conn, angle);
                break;
            }
        }

        //usleep(100000);
    }
    
    bc_disconnect(conn);
    return EXIT_SUCCESS;
}
