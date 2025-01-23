#ifndef BATTLE_C_H
#define BATTLE_C_H

#include "stdbool.h"
#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Opaque Connection object
 */
typedef struct BC_Connection_ {
} BC_Connection;

/**
 * Opaque List
 */
typedef struct BC_List_ {

} BC_List;

typedef struct BC_Vector3_ {
  double x;
  double y;
  double z;
} BC_Vector3;

typedef struct BC_Vector2_ {
  double x;
  double y;
} BC_Vector2;

enum BC_ObjectType { OT_PLAYER, OT_WALL, OT_BOOST };

typedef struct BC_PlayerData_ {
  int id;
  BC_Vector3 position;
  BC_Vector3 speed;
  int health;
  int score;
  int armor;
  bool is_dead;
} BC_PlayerData;

typedef struct BC_BoostObjectData_ {
  int health;
} BC_BoostObjectData;

typedef struct BC_MapObject_ {
  enum BC_ObjectType type;
  int id;
  BC_Vector3 position;
  BC_Vector3 speed;
  int health;
} BC_MapObject;

typedef struct BC_WorldInfo_ {
  uint64_t map_x;
  uint64_t map_y;
  uint32_t player_count;
  bool auto_shoot_enabled;
  bool radar_enabled;
} BC_WorldInfo;

typedef enum BC_ShootResultFailReason_ {
  UNKNOWN,
  COOLDOWN,
  MISS
} BC_ShootResultFailReason;

typedef struct BC_ShootResult_ {
  bool success;           // Whether the shot was successful
  uint64_t target_id;     // ID of the target (if hit)
  uint64_t damage_points; // Damage dealt to the target
  bool target_destroyed;  // Whether the target was destroyed
  BC_ShootResultFailReason fail_reason;
} BC_ShootResult;

/**
 * @brief Establishes a connection to a server at the specified address and
 * port.
 *
 * This function creates a new connection to a remote server using the given
 * IP address or hostname and port number. It returns a handle to an opaque
 * `BC_Connection` object that can be used for further interactions.
 *
 * @param address The IP address or hostname of the server to connect to.
 * @param port The port number on which the server is listening.
 * @return A pointer to a `BC_Connection` object representing the connection.
 */
BC_Connection *bc_connect(const char *address, int port);

/**
 * @brief Retrieves information about the current game world.
 *
 * This function queries the server to get the latest information about the
 * world state, such as map size, objects, or other environmental data.
 *
 * @param connection A pointer to a `BC_Connection` object representing the
 * active connection.
 * @return A `BC_WorldInfo` object containing world information.
 */
BC_WorldInfo bc_get_world_info(BC_Connection *connection);

/**
 * @brief Disconnects from the server and cleans up the connection.
 *
 * This function gracefully closes the connection to the server and releases
 * any associated resources.
 *
 * @param connection A pointer to the `BC_Connection` object to be disconnected.
 */
void bc_disconnect(BC_Connection *connection);

/**
 * @brief Retrieves data about the local player.
 *
 * This function fetches the current status and data of the local player,
 * such as position, health, and other gameplay-related attributes.
 *
 * @param connection A pointer to the `BC_Connection` object representing the
 * active connection.
 * @return A `BC_PlayerData` object containing the player's data.
 */
BC_PlayerData bc_get_player_data(BC_Connection *connection);

/**
 * @brief Sets the player's movement speed in the world.
 *
 * This function updates the player's movement speed in the specified direction
 * using the given X, Y, and Z velocity components.
 *
 * @param connection A pointer to the `BC_Connection` object representing the
 * active connection.
 * @param x The X-axis velocity component.
 * @param y The Y-axis velocity component.
 * @param z The Z-axis velocity component.
 */
void bc_set_speed(BC_Connection *connection, double x, double y, double z);

/**
 * @brief Performs a shooting action in the specified direction.
 *
 * This function sends a command to the server to shoot in the direction
 * specified by the given angle (in radians).
 *
 * @param connection A pointer to the `BC_Connection` object representing the
 * active connection.
 * @param angle The angle (in radians) at which to shoot.
 */
BC_ShootResult bc_shoot(BC_Connection *connection, double angle);

/**
 * @brief Sends a radar ping to detect nearby objects.
 *
 * This function triggers a radar scan, returning a list of nearby objects
 * detected by the radar. Each object is represented as a `MapObject_`.
 *
 * @param connection A pointer to the `BC_Connection` object representing the
 * active connection.
 * @return A pointer to a `BC_List` containing detected objects.
 */
BC_List *bc_radar_ping(BC_Connection *connection);

/**
 * @brief Retrieves the next element in a linked list.
 *
 * This function advances to the next node in a `BC_List`. If the current
 * node is the last one, it returns `nullptr`.
 *
 * @param bc_list A pointer to the current `BC_List` node.
 * @return A pointer to the next `BC_List` node, or `nullptr` if at the end.
 */
BC_List *bc_ll_next(BC_List *bc_list);

/**
 * @brief Retrieves the value stored in the current linked list node.
 *
 * This function returns the data stored in the current node of a `BC_List`.
 *
 * @param bc_list A pointer to the current `BC_List` node.
 * @return A pointer to the data stored in the current node.
 */
void *bc_ll_value(BC_List *bc_list);

/**
 * @brief Frees the memory associated with a linked list.
 *
 * This function releases all memory allocated for a `BC_List`, including
 * the list nodes and their contents.
 *
 * @param bc_list A pointer to the head of the `BC_List` to be freed.
 */
void bc_ll_free(BC_List *bc_list);

/**
 * @brief Sets a callback handler to be invoked when the game ends.
 *
 * This function allows the user to define a callback that will be triggered
 * whenever the game ends. The callback function should handle any cleanup,
 * notifications, or actions required after the game has concluded.
 *
 * @param connection
 *        A pointer to the BC_Connection object representing the active
 *        connection. This connection is used to associate the callback
 *        with the specific game session.
 *
 * @param game_ended_handler
 *        A function pointer to the user-defined callback function that will
 *        be executed when the game ends. The callback function takes a
 *        BC_PlayerData object as a parameter, which provides details about
 *        the player's status or data at the end of the game.
 *
 * @note
 * - Ensure the `connection` object is valid and properly initialized before
 *   invoking this function.
 * - The `game_ended_handler` callback must conform to the specified signature:
 *   `void callback_function(BC_PlayerData player_data);`.
 * - The `game_ended_handler` callback is optional. Passing NULL will unset
 *   any previously set handler.
 */
void bc_set_game_ended_handler(
    BC_Connection *connection,
    void (*game_ended_handler)(BC_PlayerData player_data));

/**
 * @brief Sets a callback handler to be invoked when the game starts.
 *
 * This function allows the user to define a callback that will be triggered
 * whenever a game starts. The callback function should handle any setup,
 * initialization, or notifications required when the game begins.
 *
 * @param connection
 *        A pointer to the BC_Connection object representing the active
 *        connection. This connection is used to associate the callback
 *        with the specific game session.
 *
 * @param game_started_handler
 *        A function pointer to the user-defined callback function that will
 *        be executed when the game starts. The callback function does not
 *        take any parameters and should conform to the following signature:
 *        `void callback_function();`.
 *
 * @note
 * - Ensure the `connection` object is valid and properly initialized before
 *   invoking this function.
 * - The `game_started_handler` callback is optional. Passing NULL will unset
 *   any previously set handler.
 * - The callback is expected to execute quickly to avoid delaying game start
 *   operations.
 */
void bc_set_game_started_handler(BC_Connection *connection,
                                 void (*game_started_handler)());

#ifdef __cplusplus
}
#endif

#endif
