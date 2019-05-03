#include "utility.h"

void init_rng()
{
    randomNumber.Instance = RNG;
    __HAL_RCC_RNG_CLK_ENABLE();
    HAL_RNG_Init(&randomNumber);
}

uint16_t random(uint16_t lower_limit, uint16_t upper_limit)
{
    return ((HAL_RNG_GetRandomNumber(&randomNumber) % (upper_limit - lower_limit)) + lower_limit);
}

uint8_t throwD6()
{
    return (uint8_t)(random(0, 6) + 1);
}

stats_t get_random_stats(uint16_t level, entity_type_t type)
{
  stats_t stats;
  switch (type) {
  case HERO_ENTITY:
    stats.max_health = 20 + (3 * throwD6());
    stats.cur_health = stats.max_health;
    stats.defence = 2 * throwD6();
    stats.attack = 5 + throwD6();
    break;
  case BOSS_ENTITY:
    stats.max_health = (2 * level * throwD6()) + throwD6();
    stats.cur_health = stats.max_health;
    stats.defence = (uint16_t) ((((float) level / 2.0) * throwD6()) + ((float) throwD6() / 2.0));
    stats.attack = (level * throwD6()) + level;
    break;
  case SKELETON_ENTITY:
    stats.max_health = 2 * level * throwD6();
    stats.cur_health = stats.max_health;
    stats.defence = (uint16_t) ((float) level / 2.0 * throwD6());
    stats.attack = level * throwD6();
    break;
  default:
    stats.cur_health = 0;
    break;
  }
  return stats;
}
