#include "radar.h"

RadarObject *addRadarObject(RadarObject *head, BC_MapObject *map_object) {
    RadarObject *new_obj = (RadarObject *)malloc(sizeof(RadarObject));
    if (new_obj == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return head;
    }

    new_obj->x = map_object->position.x;
    new_obj->y = map_object->position.y;
    new_obj->speed_x = map_object->speed.x;
    new_obj->speed_y = map_object->speed.y;
    new_obj->type = map_object->type;
    new_obj->id = map_object->id;
    new_obj->health = map_object->health;
    new_obj->next = head;

    return new_obj;
}

RadarObject *displayAndStoreRadarData(BC_List *radarData) {
    RadarObject *head = NULL;

    if (radarData == NULL) {
        printf("Radar data: empty\n");
        return NULL;
    }

    //printf("Radar data:\n");

    while (radarData != NULL) {
        BC_MapObject *map_object = (BC_MapObject *)bc_ll_value(radarData);
        if (map_object != NULL) {
            //printf("Objet détecté → x = %.2f, y = %.2f\n", map_object->position.x, map_object->position.y);
            //printf("Type = %d, ID = %d, Santé = %d \n", map_object->type, map_object->id, map_object->health);
            //printf("Vitesse → vx = %.2f, vy = %.2f\n", map_object->speed.x, map_object->speed.y);

            head = addRadarObject(head, map_object);
        }

        radarData = bc_ll_next(radarData);
    }

    //printf("\nFin de l'analyse radar.\n");
    return head;
}

void freeRadarObjects(RadarObject **head) {
    RadarObject *tmp;
    while (*head != NULL) {
        tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }
    *head = NULL;
}
