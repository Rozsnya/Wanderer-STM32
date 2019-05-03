#include "TS_Control.h"

void process_touch(game_t* game)
{
  TS_StateTypeDef touch;
  BSP_TS_GetState(&touch);

  if (touch.touchX[0] > 27 && touch.touchX[0] < 77) {
    if (touch.touchY[0] > 150 && touch.touchY[0] < 200) {
      move_hero(game, HERO_UP);
    } else if (touch.touchY[0] > 200 && touch.touchY[0] < 250) {
      move_hero(game, HERO_DOWN);
    }
  } else if (touch.touchY[0] > 175 && touch.touchY[0] < 225) {
    if(touch.touchX[0] > 377 && touch.touchX[0] < 427){
      move_hero(game, HERO_LEFT);
    } else if (touch.touchX[0] > 428 && touch.touchX[0] < 478){
      move_hero(game, HERO_RIGHT);
    }
  } else if (touch.touchX[0] > 100 && touch.touchX[0] < (BSP_LCD_GetXSize() - 100)) {
    hero_battle(game);
  }
}
