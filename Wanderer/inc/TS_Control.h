#ifndef TS_CONTROL_H_
#define TS_CONTROL_H_

#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "game.h"

void process_touch(game_t* game);
void player_attack();

#endif /* TS_CONTROL_H_ */
