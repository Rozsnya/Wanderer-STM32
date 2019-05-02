#ifndef GAME_TYPEDEFS_H_
#define GAME_TYPEDEFS_H_

#define MAP_SIZE 10
#define MAX_SKELETONS 3
#define WALL_NUM 39

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} pos_t; //tile pos, not pixel pos

typedef struct {
    uint8_t is_alive;
    uint16_t max_health;
    uint16_t cur_health;
    uint16_t attack;
    uint16_t defence;
} stats_t;

typedef enum {
    HERO_UP,
    HERO_RIGHT,
    HERO_DOWN,
    HERO_LEFT
} hero_direction_t;

typedef struct {
    pos_t pos;
    stats_t stats;
    uint8_t has_key;
} skeleton_t;

typedef struct {
    pos_t pos;
    stats_t stats;
} boss_t;

typedef struct {
    pos_t pos;
    stats_t stats;
    hero_direction_t direction;
} hero_t;

typedef union {
    boss_t boss;
    skeleton_t skeleton;
} enemy_t;

typedef enum {
    HERO_ENTITY,
    BOSS_ENTITY,
    SKELETON_ENTITY,
} entity_type_t;

typedef struct {
    uint16_t level;
    pos_t walls[WALL_NUM];
    hero_t hero;
    boss_t boss;
    skeleton_t skeletons[MAX_SKELETONS];
    uint8_t num_of_skeletons;
    uint8_t boss_killed : 1;
    uint8_t key_obtained : 1;
} game_t;

#endif /* GAME_TYPEDEFS_H_ */
