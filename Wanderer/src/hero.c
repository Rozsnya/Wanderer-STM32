#include "hero.h"

void levelup_hero(game_t* game)
{
  game->hero.pos = (pos_t ) { 0, 0 };

  game->hero.stats.attack += throwD6();
  game->hero.stats.defence += throwD6();
  game->hero.stats.max_health += throwD6();

  uint8_t hp_restore = random(0, 100);
  if (hp_restore < 10) { //full hp
    game->hero.stats.cur_health = game->hero.stats.max_health;
  } else if (hp_restore >= 10 && hp_restore < 50) { // +33% hp
    game->hero.stats.cur_health += game->hero.stats.max_health * 0.33;
  } else { // +10% hp
    game->hero.stats.cur_health += game->hero.stats.max_health * 0.1;
  }
}

void create_hero(game_t* game)
{
  hero_t hero = {
      .direction = HERO_DOWN,
      .pos = {0,0},
      .stats = get_random_stats(0, HERO_ENTITY)
  };

  game->hero = hero;
}

uint8_t is_valid_move(const game_t* game, hero_direction_t dir)
{
  pos_t temp;
  switch(dir) {
  case HERO_UP:
    temp = (pos_t ) { game->hero.pos.x, game->hero.pos.y - 1 };
    break;
  case HERO_RIGHT:
    temp = (pos_t ) { game->hero.pos.x + 1, game->hero.pos.y };
    break;
  case HERO_DOWN:
    temp = (pos_t ) { game->hero.pos.x, game->hero.pos.y + 1 };
    break;
  case HERO_LEFT:
    temp = (pos_t ) { game->hero.pos.x - 1, game->hero.pos.y };
    break;
  }
  for(uint8_t i = 0; i < WALL_NUM; i++) {
      if(game->walls[i].x == temp.x &&
         game->walls[i].y == temp.y) {
        return 0;
      }
    }
  return 1;
}

void move_hero(game_t* game, hero_direction_t dir)
{
  DMA2D_DrawImage((uint32_t)FLOOR_DATA, 105 + (game->hero.pos.x * 27), 1 + (game->hero.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
  if(!is_valid_move(game, dir) || game->hero.stats.cur_health <= 0) {
    return;
  }
  switch(dir) {
  case HERO_UP:
    if(game->hero.pos.y > 0) {
      game->hero.pos.y--;
    }
    break;
  case HERO_RIGHT:
    if(game->hero.pos.x < (MAP_SIZE - 1)) {
      game->hero.pos.x++;
    }
    break;
  case HERO_DOWN:
    if(game->hero.pos.y < (MAP_SIZE - 1)) {
      game->hero.pos.y++;
    }
    break;
  case HERO_LEFT:
    if(game->hero.pos.x > 0) {
      game->hero.pos.x--;
    }
    break;
  default:
    break;
  }
  game->hero.direction = dir;
}

void show_hero(game_t* game)
{
  switch (game->hero.direction) {
  case HERO_UP:
    DMA2D_DrawImage((uint32_t)HERO_UP_DATA, 105 + (game->hero.pos.x * 27), 1 + (game->hero.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
    break;
  case HERO_RIGHT:
    DMA2D_DrawImage((uint32_t)HERO_RIGHT_DATA, 105 + (game->hero.pos.x * 27), 1 + (game->hero.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
    break;
  case HERO_DOWN:
    DMA2D_DrawImage((uint32_t)HERO_DOWN_DATA, 105 + (game->hero.pos.x * 27), 1 + (game->hero.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
    break;
  case HERO_LEFT:
    DMA2D_DrawImage((uint32_t)HERO_LEFT_DATA, 105 + (game->hero.pos.x * 27), 1 + (game->hero.pos.y * 27), TEXTURE_SIZE, TEXTURE_SIZE);
    break;
  default:
    break;
  }
}

int8_t is_on_enemy(game_t* game)
{
  for (uint8_t i = 0; i < (MAX_SKELETONS + 1); i++) {
    if ((game->hero.pos.x == game->enemy_positions[i].x) && (game->hero.pos.y == game->enemy_positions[i].y)) {
      return i;
    }
  }
  return -1;
}

void hero_battle(game_t* game)
{
  int8_t enemy = is_on_enemy(game);
  if(enemy == -1) {
    return;
  }

  uint16_t hero_attack = game->hero.stats.attack + (2 * throwD6());

  if(enemy == 0) { //boss
    int16_t damage = (hero_attack - game->boss.stats.defence);
    if(damage > 0) {
      game->boss.stats.cur_health -= damage;
    }
    if (game->boss.stats.cur_health > 0) {
      int16_t boss_damage = (game->boss.stats.attack + (2 * throwD6()));
      if (boss_damage > 0) {
        game->hero.stats.cur_health -= boss_damage;
      }
    }
  } else { //skeletons
    int16_t damage = (hero_attack - game->skeletons[enemy - 1].stats.defence);
    if(damage > 0) {
      game->skeletons[enemy - 1].stats.cur_health -= damage;
    }
    if (game->skeletons[enemy - 1].stats.cur_health > 0) {
      int16_t skeleton_damage = (game->skeletons[enemy - 1].stats.attack + (2 * throwD6()));
      if (skeleton_damage > 0) {
        game->hero.stats.cur_health -= skeleton_damage;
      }
    }
  }
}
