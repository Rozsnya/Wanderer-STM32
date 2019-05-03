#ifndef HERO_H_
#define HERO_H_

#include "utility.h"
#include "images.h"
#include "dma2d.h"
#include "map.h"

void levelup_hero(game_t* game);
void create_hero(game_t* game);
void move_hero(game_t* game, hero_direction_t dir);
void show_hero(game_t* game);
#endif /* HERO_H_ */
