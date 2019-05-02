#include "enemy.h"

void place_enemies(game_t* game)
{
    place_boss(game);

    uint8_t keyholder = random(0, MAX_SKELETONS);
    for(uint8_t i = 0; i < MAX_SKELETONS; i++) {
        place_skeleton(game, keyholder == i);
    }
}

skeleton_t create_skeleton(uint16_t level, const pos_t* pos, uint8_t is_keyholder)
{
    skeleton_t skeleton = {
        .pos = {pos->x, pos->y},
        .stats = get_random_stats(level, SKELETON_ENTITY),
        .has_key = is_keyholder
    };
    return skeleton;
}

void place_skeleton(game_t* game, uint8_t is_keyholder)
{
    pos_t pos;
    do {
        pos = get_random_pos();
    } while(!is_valid_enemy_pos(game, &pos));

    game->skeletons[game->num_of_skeletons] = create_skeleton(game->level, &pos, is_keyholder);
    game->num_of_skeletons++;
}

boss_t create_boss(uint16_t level, const pos_t* pos)
{
    boss_t boss = {
        .pos = {pos->x, pos->y},
        .stats = get_random_stats(level, BOSS_ENTITY)
    };
    return boss;
}

void place_boss(game_t* game)
{
    pos_t pos;
    do {
        pos = get_random_pos();
    } while (!is_valid_enemy_pos(game, &pos));

    game->boss = create_boss(game->level, &pos);
}

pos_t get_random_pos()
{
    pos_t pos;
    pos.x = random(0, MAP_SIZE);
    pos.y = random(0, MAP_SIZE);

    return pos;
}

uint8_t is_valid_enemy_pos(const game_t* game, const pos_t* pos)
{
  if((pos->x + pos->y) < 6) {
    return 0;
  }

  for(uint8_t i = 0; i < WALL_NUM; i++) {
    if(game->walls[i].pos.x == pos->x &&
       game->walls[i].pos.y == pos->y) {
      return 0;
    }
  }

  if((pos->x == game->boss.pos.x) && (pos->y == game->boss.pos.y)) {
    return 0;
  }

  for(uint8_t i = 0; i < MAX_SKELETONS; i++) {
    if((pos->x == game->skeletons[i].pos.x) && (pos->y == game->skeletons[i].pos.y)) {
        return 0;
      }
  }
  return 1;
}

void move_skeletons(game_t* game)
{
  for(uint8_t i = 0; i < game->num_of_skeletons; i++) {
    uint8_t random_dir = random(0, 4);
    switch(random_dir) {
    case 0: //up
      if (game->skeletons[i].pos.y > 0) {
        game->skeletons[i].pos.y--;
      }
      break;
    case 1: //right
      if (game->skeletons[i].pos.x < (MAP_SIZE - 1)) {
        game->skeletons[i].pos.x++;
      }
      break;
    case 2: //down
      if (game->skeletons[i].pos.y < (MAP_SIZE - 1)) {
        game->skeletons[i].pos.y++;
      }
      break;
    case 3: //left
      if (game->skeletons[i].pos.x > 0) {
        game->skeletons[i].pos.x--;
      }
      break;
    default:
      break;
    }
  }
}

void show_skeletons(game_t* game)
{
  for(uint8_t i = 0; i < game->num_of_skeletons; i++) {
    DMA2D_DrawImage(SKELETON_DATA, 105 + (game->skeletons[i].pos.x * 27), 1 + (game->skeletons[i].pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
  }
}

void move_boss(game_t* game)
{
  uint8_t random_dir = random(0, 4);
  switch (random_dir) {
  case 0: //up
    if (game->boss.pos.y > 0) {
      game->boss.pos.y--;
    }
    break;
  case 1: //right
    if (game->boss.pos.x < (MAP_SIZE - 1)) {
      game->boss.pos.x++;
    }
    break;
  case 2: //down
    if (game->boss.pos.y < (MAP_SIZE - 1)) {
      game->boss.pos.y++;
    }
    break;
  case 3: //left
    if (game->boss.pos.x > 0) {
      game->boss.pos.x--;
    }
    break;
  default:
    break;
  }
}

void show_boss(game_t* game)
{
  DMA2D_DrawImage(BOSS_DATA, 105 + (game->boss.pos.x * 27), 1 + (game->boss.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
}
