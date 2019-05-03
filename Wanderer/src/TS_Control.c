#include "TS_Control.h"


void process_touch(game_t* game)
{
  TS_StateTypeDef touch;
  BSP_TS_GetState(&touch);

  if(touch.touchX[0] < 100 && touch.touchY[0] < 100) {
    move_hero(game, HERO_UP);
  } else if(touch.touchX[0] < 100 && touch.touchY[0] > BSP_LCD_GetYSize() - 100) {
    move_hero(game, HERO_DOWN);
  }
}
