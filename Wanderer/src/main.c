#include "SystemClockConfig.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "utility.h"
#include "game.h"
#include "map.h"
#include "dma2d.h"
#include "images.h"
#include "TS_Control.h"
#include "border.h"
#include <stdio.h>

volatile uint8_t touch_flag;

uint32_t last_debounce_time = 0;    // the last time the output pin was toggled
const uint32_t debounce_delay = 300;    // the debounce time in ms (increase if the output flickers)


int main(void) {

	HAL_Init();
	SystemClock_Config();

	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_TS_Init(480, 272);
	BSP_TS_ITConfig();

  map_init();
	init_rng();
	draw_arrow_keys();
	draw_icons();

	BSP_LED_Init(LED_GREEN);
  char stat_string[50];
	game_t game = start_game();

	while (1) {
	  sprintf(stat_string, "%d/%d", game.hero.stats.cur_health, game.hero.stats.max_health);
	  BSP_LCD_DisplayStringAt(30, 10, (uint8_t*)stat_string, LEFT_MODE);
	  sprintf(stat_string, "%d", game.hero.stats.attack);
	  BSP_LCD_DisplayStringAt(30, 37, (uint8_t*)stat_string, LEFT_MODE);
	  sprintf(stat_string, "%d", game.hero.stats.defence);
	  BSP_LCD_DisplayStringAt(30, 64, (uint8_t*)stat_string, LEFT_MODE);

	  if(touch_flag) {
	    process_touch(&game);
	    touch_flag = 0;
	  }
	  show_hero(&game);
	  show_boss(&game);
	  show_skeletons(&game);
	}
}

void EXTI15_10_IRQHandler()
{
    HAL_GPIO_EXTI_IRQHandler(TS_INT_PIN);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
 {
	uint32_t current_time = HAL_GetTick();
	if (current_time < last_debounce_time + debounce_delay) {
		return;
	}

	last_debounce_time = current_time;
	if (GPIO_Pin == TS_INT_PIN) {
		touch_flag = 1;
	}
}

/*
 * timers for enemy movement
 * safe zone at start (enemies staying away)
 * enemies attacking at contact, once per move
 * rework strike system
 * attacker gets advantage?
 *
 * stat drawing
 * tweak monster spawning (50% +1 lvl 10% +2lvl
 *
 * read the specifications
 * */
