#ifndef UTILITY_H_
#define UTILITY_H_

#include "stm32f7xx.h"
#include "stm32746g_discovery.h"
#include "game_typedefs.h"

RNG_HandleTypeDef randomNumber;

void init_rng();
uint16_t random(uint16_t lower_limit, uint16_t upper_limit);
uint8_t throwD6();

stats_t get_random_stats(uint16_t level, entity_type_t type);

#endif /* UTILITY_H_ */
