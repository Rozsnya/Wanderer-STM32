#include "game.h"
#include <memory.h>

game_t start_game(uint16_t level, stats_t hero_stats)
{
  game_t game;
  memset(&game, 0, sizeof(game));
  game.level = level;
  create_hero(&game, hero_stats);
  place_walls(&game);
  place_enemies(&game);
  return game;
}

uint8_t level_done(game_t* game)
{
  if(game->boss.stats.cur_health <= 0) {
    game->boss_killed = 1;
  }
  for(uint8_t i = 0; i < MAX_SKELETONS; i++) {
    if(game->skeletons[i].has_key && game->skeletons[i].stats.cur_health <= 0) {
      game->key_obtained = 1;
    }
  }

  if(game->key_obtained && game->boss_killed) {
    levelup_hero(game);
    return 1;
  }
  return 0;
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
      game->walls[j] = (pos_t)get_2d_pos(i);
      j++;
    }
  }
}

pos_t get_2d_pos(uint8_t i)
{
  return (pos_t) {i % MAP_SIZE, i / MAP_SIZE};
}
