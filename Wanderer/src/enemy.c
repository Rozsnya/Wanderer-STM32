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

    game->enemy_positions[game->num_of_skeletons+1] = pos;
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

    game->enemy_positions[0] = pos;
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
  if((pos->x + pos->y) < 4) {
    return 0;
  }

  for(uint8_t i = 0; i < WALL_NUM; i++) {
    if(game->walls[i].x == pos->x &&
       game->walls[i].y == pos->y) {
      return 0;
    }
  }

  for(uint8_t i = 0; i < (MAX_SKELETONS + 1); i++) {
    if((pos->x == game->enemy_positions[i].x) && (pos->y == game->enemy_positions[i].y)) {
      return 0;
    }
  }

  return 1;
}

void move_skeletons(game_t* game)
{
  for(uint8_t i = 0; i < game->num_of_skeletons; i++) {
    DMA2D_DrawImage((uint32_t)FLOOR_DATA, 105 + (game->skeletons[i].pos.x * 27), 1 + (game->skeletons[i].pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
    if(game->skeletons[i].stats.cur_health <= 0 || ((game->skeletons[i].pos.x == game->hero.pos.x) && (game->skeletons[i].pos.y == game->hero.pos.y))){
      continue;
    }
    uint8_t random_dir = random(0, 4);
    switch(random_dir) {
    case 0: //up
      if (game->skeletons[i].pos.y > 0) {
        game->skeletons[i].pos.y--;
        if (!is_valid_enemy_pos(game, &game->skeletons[i].pos)) {
          game->skeletons[i].pos.y++;
        }
      }
      break;
    case 1: //right
      if (game->skeletons[i].pos.x < (MAP_SIZE - 1)) {
        game->skeletons[i].pos.x++;
        if (!is_valid_enemy_pos(game, &game->skeletons[i].pos)) {
          game->skeletons[i].pos.x--;
        }
      }
      break;
    case 2: //down
      if (game->skeletons[i].pos.y < (MAP_SIZE - 1)) {
        game->skeletons[i].pos.y++;
        if (!is_valid_enemy_pos(game, &game->skeletons[i].pos)) {
          game->skeletons[i].pos.y--;
        }
      }
      break;
    case 3: //left
      if (game->skeletons[i].pos.x > 0) {
        game->skeletons[i].pos.x--;
        if (!is_valid_enemy_pos(game, &game->skeletons[i].pos)) {
          game->skeletons[i].pos.x++;
        }
      }
      break;
    default:
      break;
    }
    game->enemy_positions[i+1] = game->skeletons[i].pos;
  }
}

void show_skeletons(game_t* game)
{
  for(uint8_t i = 0; i < game->num_of_skeletons; i++) {
    if (game->skeletons[i].stats.cur_health <= 0) {
      continue;
    }
    DMA2D_DrawImage((uint32_t)SKELETON_DATA, 105 + (game->skeletons[i].pos.x * 27), 1 + (game->skeletons[i].pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
  }
}

void move_boss(game_t* game)
{
  DMA2D_DrawImage((uint32_t)FLOOR_DATA, 105 + (game->boss.pos.x * 27), 1 + (game->boss.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);

  if(game->boss.stats.cur_health <= 0 || ((game->boss.pos.x == game->hero.pos.x) && (game->boss.pos.y == game->hero.pos.y))) {
    return;
  }

  uint8_t random_dir = random(0, 4);
  switch (random_dir) {
  case 0: //up
    if (game->boss.pos.y > 0) {
      game->boss.pos.y--;
      if (!is_valid_enemy_pos(game, &game->boss.pos)) {
        game->boss.pos.y++;
      }
    }
    break;
  case 1: //right
    if (game->boss.pos.x < (MAP_SIZE - 1)) {
      game->boss.pos.x++;
      if (!is_valid_enemy_pos(game, &game->boss.pos)) {
        game->boss.pos.x--;
      }
    }
    break;
  case 2: //down
    if (game->boss.pos.y < (MAP_SIZE - 1)) {
      game->boss.pos.y++;
      if (!is_valid_enemy_pos(game, &game->boss.pos)) {
        game->boss.pos.y--;
      }
    }
    break;
  case 3: //left
    if (game->boss.pos.x > 0) {
      game->boss.pos.x--;
      if (!is_valid_enemy_pos(game, &game->boss.pos)) {
        game->boss.pos.x++;
      }
    }
    break;
  default:
    break;
  }
  game->enemy_positions[0] = game->boss.pos;
}

void show_boss(game_t* game)
{
  if (game->boss.stats.cur_health <= 0) {
    return;
  }
  DMA2D_DrawImage((uint32_t)BOSS_DATA, 105 + (game->boss.pos.x * 27), 1 + (game->boss.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
}
