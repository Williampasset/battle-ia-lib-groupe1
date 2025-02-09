# Battle-C bot 

## Installation 

### Pré-requis:
- Docker 
- Meson
- Ninja

### Compilation 
#### Avec Docker
```sh
docker build -t battle_bot -f Dockerfile .
```

#### Sans Docker
```sh
meson setup builddir
meson compile -C builddir
```

### Lancement 
#### Avec Docker
```sh
docker run battle_bot
```

#### Sans Docker
```sh
./builddir/battle_c_bot
```

### Mode Débogage
Pour activer le mode débogage, configurez le projet avec l'option `-Ddebug=true` :
```sh
meson setup builddir -Ddebug=true
meson compile -C builddir
```

## Scoring

- Toucher un ennemi : 20 points 
- Détruire un ennemi: 50 points
- Récupérer un boost: 30 points

## Fonctionnalités du Bot

### Déplacement
Le bot se déplace en direction du boost le plus proche. Si un obstacle est détecté sur le chemin, le bot change de direction pour éviter l'obstacle.

#### Exemple de Code pour le Déplacement
```c
void move_towards_closest_boost(BC_Connection *conn, BC_Vector3 robot_pos, RadarData *radar_data) {
    BC_MapObject *closest_boost = find_closest_boost(conn, robot_pos);
    if (closest_boost != NULL) {
        DEBUG_PRINT(("Closest boost found at: (%f, %f, %f)\n", closest_boost->position.x, closest_boost->position.y, closest_boost->position.z));
        
        // Calculer l'angle vers le boost le plus proche
        double dx = closest_boost->position.x - robot_pos.x;
        double dy = closest_boost->position.y - robot_pos.y;
        double angle_to_boost = atan2(dy, dx) * 180 / M_PI;

        // Mettre à jour la vitesse pour se diriger vers le boost
        double vx = cos(angle_to_boost * M_PI / 180) * SPEED * 2;
        double vy = sin(angle_to_boost * M_PI / 180) * SPEED * 2;
        BC_Vector3 new_position = {robot_pos.x + vx, robot_pos.y + vy, robot_pos.z};

        // Vérifier si la nouvelle position est bloquée par un obstacle
        if (is_position_blocked(new_position, radar_data)) {
            // Si bloqué, imprimer un message d'avertissement et choisir une direction aléatoire
            DEBUG_PRINT(("Obstacle detected on the way to the boost!\n"));
            double angle = rand() % 360;
            vx = cos(angle * M_PI / 180) * SPEED * 2;
            vy = sin(angle * M_PI / 180) * SPEED * 2;
        }

        bc_set_speed(conn, vx, vy, 0);
    } else {
        // Si aucun boost n'est trouvé, continuer à se déplacer de manière aléatoire
        double angle = rand() % 360;
        double vx = cos(angle * M_PI / 180) * SPEED * 2;
        double vy = sin(angle * M_PI / 180) * SPEED * 2;
        bc_set_speed(conn, vx, vy, 0);
    }
}
```

### Radar
Le radar du bot détecte les joueurs, les obstacles et les bonus sur le terrain. Les données du radar sont mises à jour régulièrement pour permettre au bot de prendre des décisions en temps réel.

#### Exemple de Code pour le Radar
```c
void update_radar_data(BC_Connection *conn, RadarData *radar_data) {
    BC_List *list = bc_radar_ping(conn);

    radar_data->players_count = 0;
    radar_data->obstacles_count = 0;
    radar_data->bonuses_count = 0;

    while (list) {
        BC_MapObject *obj = (BC_MapObject *)bc_ll_value(list);
        
        switch (obj->type) {
            case 0: // Joueurs
                radar_data->players = realloc(radar_data->players, (radar_data->players_count + 1) * sizeof(BC_MapObject *));
                radar_data->players[radar_data->players_count++] = obj;
                break;
            case 1: // Obstacles
                radar_data->obstacles = realloc(radar_data->obstacles, (radar_data->obstacles_count + 1) * sizeof(BC_MapObject *));
                radar_data->obstacles[radar_data->obstacles_count++] = obj;
                break;
            case 2: // Bonus
                radar_data->bonuses = realloc(radar_data->bonuses, (radar_data->bonuses_count + 1) * sizeof(BC_MapObject *));
                radar_data->bonuses[radar_data->bonuses_count++] = obj;
                break;
        }
        list = bc_ll_next(list);
    }
}
```

### Tir
Le bot tire sur les ennemis lorsqu'ils sont à portée de tir. La fonction `is_shootable` vérifie si un ennemi est à portée et la fonction `bc_shoot` est utilisée pour tirer.

#### Exemple de Code pour le Tir
```c
void *shooting_thread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    BC_Connection *conn = thread_args->conn;
    BC_PlayerData *data = thread_args->data;
    RadarData *radar_data = thread_args->radar_data;

    while (!data->is_dead) {
        for (int i = 0; i < radar_data->players_count; i++) {
            BC_MapObject *player = radar_data->players[i];
            if (is_shootable(data->position, player->position, radar_data)) {
                double angle = calculate_angle(data->position, player->position);
                bc_shoot(conn, angle);
                break;
            }
        }
        usleep(DELAY);
    }

    return NULL;
}
```

## Structure du Projet

### Fichiers Sources
- `src/main.c` : Point d'entrée principal du programme.
- `src/radar.c` : Gestion des données du radar et des mouvements.
- `src/shoot.c` : Gestion des actions de tir.
- `src/utils.c` : Fonctions utilitaires.
- `src/move.c` : Fonctions de mouvement.

### Fichiers d'En-tête
- `include/main.h` : Déclarations pour `main.c`.
- `include/radar.h` : Déclarations pour `radar.c`.
- `include/shoot.h` : Déclarations pour `shoot.c`.
- `include/utils.h` : Déclarations pour `utils.c`.
- `include/move.h` : Déclarations pour `move.c`.
- `include/debug.h` : Macro de débogage.

## Utilisation des Threads
Le programme utilise des threads pour gérer les mouvements et les actions de tir de manière simultanée. Les threads sont créés et gérés dans `main.c`.

### Exemple de Code
#### Création et Lancement des Threads
```c
pthread_t movement_tid, shooting_tid;
pthread_create(&movement_tid, NULL, movement_thread, &thread_args);
pthread_create(&shooting_tid, NULL, shooting_thread, &thread_args);

while (!data.is_dead) {
    data = bc_get_player_data(conn);

    if (time(NULL) - lastping > 1) {
        lastping = time(NULL);
        update_radar_data(conn, &radar_data);
    }

    usleep(DELAY);
}

pthread_join(movement_tid, NULL);
pthread_join(shooting_tid, NULL);
```

### Débogage
Les messages de débogage sont contrôlés par la macro `DEBUG_PRINT` définie dans `debug.h`. Pour activer les messages de débogage, compilez le projet avec l'option `-DDEBUG`.

#### Exemple de Message de Débogage
```c
DEBUG_PRINT(("Closest boost found at: (%f, %f, %f)\n", closest_boost->position.x, closest_boost->position.y, closest_boost->position.z));
```

## Contribuer
Les contributions sont les bienvenues ! Veuillez soumettre des pull requests ou ouvrir des issues pour signaler des bugs ou proposer des améliorations.

## Licence
Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.