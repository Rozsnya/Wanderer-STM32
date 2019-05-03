#ifndef ENEMY_H_
#define ENEMY_H_

#include "utility.h"
#include "dma2d.h"
#include "images.h"
#include "map.h"

void place_enemies(game_t* game);

skeleton_t create_skeleton(uint16_t level, const pos_t* pos, uint8_t is_keyholder);
void place_skeleton(game_t* game, uint8_t is_keyholder);
void show_skeletons(game_t* game);

boss_t create_boss(uint16_t level, const pos_t* pos);
void place_boss(game_t* game);
void show_boss(game_t* game);

pos_t get_random_pos();
uint8_t is_valid_enemy_pos(const game_t* game, const pos_t* pos);

void move_boss(game_t* game);
void move_skeletons(game_t* game);

#endif /* ENEMY_H_ */
