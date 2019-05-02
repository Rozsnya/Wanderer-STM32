#include "game.h"
#include <memory.h>

game_t start_game()
{
  game_t game;
  memset(&game, 0, sizeof(game));
  create_hero(&game);
  place_walls(&game);
  place_enemies(&game);
  return game;
}

void next_level(game_t* game)
{
  levelup_hero(game);
  place_enemies(game);
}

void place_walls(game_t* game)
{
  uint8_t map[MAP_SIZE * MAP_SIZE] = {0,0,0,1,0,1,0,0,0,0,
                                      0,0,0,1,0,1,0,1,1,0,
                                      0,1,1,1,0,1,0,1,1,0,
                                      0,0,0,0,0,1,0,0,0,0,
                                      1,1,1,1,0,1,1,1,1,0,
                                      0,1,0,1,0,0,0,0,1,0,
                                      0,1,0,1,0,1,1,0,1,0,
                                      0,0,0,0,0,1,1,0,1,0,
                                      0,1,1,1,0,0,0,0,1,0,
                                      0,0,0,1,0,1,1,0,0,0};

  uint8_t j = 0;
  for(uint8_t i = 0; i < (MAP_SIZE * MAP_SIZE); i++) {
    if(map[i] == 1) {
      game->walls[j].pos = (pos_t)get_2d_pos(i);
      j++;
    }
  }
}

pos_t get_2d_pos(uint8_t i)
{
  return (pos_t) {i % MAP_SIZE, i / MAP_SIZE};
}

