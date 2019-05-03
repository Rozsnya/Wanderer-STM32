#ifndef GAME_H_
#define GAME_H_

#include "game_typedefs.h"
#include "utility.h"
#include "enemy.h"
#include "hero.h"

game_t start_game(uint16_t level, stats_t hero_stats);
void next_level(game_t* game);

pos_t get_2d_pos(uint8_t i);
void place_walls(game_t* game);

uint8_t level_done(game_t* game);

#endif /* GAME_H_ */
