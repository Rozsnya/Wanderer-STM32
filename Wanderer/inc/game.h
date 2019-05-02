#ifndef GAME_H_
#define GAME_H_

#include "game_typedefs.h"
#include "utility.h"
#include "enemy.h"
#include "hero.h"

game_t start_game();
void next_level(game_t* game);

pos_t get_2d_pos(uint8_t i);
void place_walls(game_t* game);

#endif /* GAME_H_ */
