#include "hero.h"

void levelup_hero(game_t* game)
{
    game->hero.stats.attack += throwD6();
    game->hero.stats.defence += throwD6();
    game->hero.stats.max_health += throwD6();

    uint8_t hp_restore = random(0,100);
    if(hp_restore < 10) { //full hp
      game->hero.stats.cur_health = game->hero.stats.max_health;
    } else if(hp_restore >= 10 && hp_restore < 50) { // +33% hp
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

void move_hero(game_t* game, hero_direction_t dir)
{
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
  //implement draw here
}