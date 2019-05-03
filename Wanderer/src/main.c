#include "SystemClockConfig.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "utility.h"
#include "game.h"
#include "enemy.h"
#include "map.h"
#include "dma2d.h"
#include "images.h"
#include "TS_Control.h"
#include "border.h"
#include <stdio.h>

volatile uint8_t touch_flag;
volatile uint8_t move_flag;

uint32_t last_debounce_time = 0;    // the last time the output pin was toggled
const uint32_t debounce_delay = 300;    // the debounce time in ms (increase if the output flickers)

TIM_HandleTypeDef EnemyMoveTimer;

void init_timer();

int main(void)
{

  HAL_Init();
  SystemClock_Config();
  init_timer();

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
  game_t game = start_game(1, get_random_stats(1, HERO_ENTITY));

  while (1) {
    sprintf(stat_string, "%d/%d", game.hero.stats.cur_health, game.hero.stats.max_health);
    BSP_LCD_DisplayStringAt(30, 10, (uint8_t*) "      ", LEFT_MODE);
    BSP_LCD_DisplayStringAt(30, 10, (uint8_t*) stat_string, LEFT_MODE);
    sprintf(stat_string, "%d", game.hero.stats.attack);
    BSP_LCD_DisplayStringAt(30, 37, (uint8_t*) "      ", LEFT_MODE);
    BSP_LCD_DisplayStringAt(30, 37, (uint8_t*) stat_string, LEFT_MODE);
    sprintf(stat_string, "%d", game.hero.stats.defence);
    BSP_LCD_DisplayStringAt(30, 64, (uint8_t*) "      ", LEFT_MODE);
    BSP_LCD_DisplayStringAt(30, 64, (uint8_t*) stat_string, LEFT_MODE);
    int hero_standing_on_enemy = is_on_enemy(&game);
    if (hero_standing_on_enemy == -1 || (game.boss.stats.cur_health < 1 && hero_standing_on_enemy == 0) ||
        (game.skeletons[hero_standing_on_enemy - 1].stats.cur_health < 1 && hero_standing_on_enemy > 0)) {
      BSP_LCD_DisplayStringAt(30, 10, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 37, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 64, (uint8_t*) "      ", RIGHT_MODE);
    } else if (hero_standing_on_enemy == 0) {
      sprintf(stat_string, "%d/%d", game.boss.stats.cur_health, game.boss.stats.max_health);
      BSP_LCD_DisplayStringAt(30, 10, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 10, (uint8_t*) stat_string, RIGHT_MODE);
      sprintf(stat_string, "%d", game.boss.stats.attack);
      BSP_LCD_DisplayStringAt(30, 37, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 37, (uint8_t*) stat_string, RIGHT_MODE);
      sprintf(stat_string, "%d", game.boss.stats.defence);
      BSP_LCD_DisplayStringAt(30, 64, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 64, (uint8_t*) stat_string, RIGHT_MODE);
    } else if (hero_standing_on_enemy != -1) {
      sprintf(stat_string, "%d/%d", game.skeletons[hero_standing_on_enemy - 1].stats.cur_health, game.skeletons[hero_standing_on_enemy - 1].stats.max_health);
      BSP_LCD_DisplayStringAt(30, 10, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 10, (uint8_t*) stat_string, RIGHT_MODE);
      sprintf(stat_string, "%d", game.skeletons[hero_standing_on_enemy - 1].stats.attack);
      BSP_LCD_DisplayStringAt(30, 37, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 37, (uint8_t*) stat_string, RIGHT_MODE);
      sprintf(stat_string, "%d", game.skeletons[hero_standing_on_enemy - 1].stats.defence);
      BSP_LCD_DisplayStringAt(30, 64, (uint8_t*) "      ", RIGHT_MODE);
      BSP_LCD_DisplayStringAt(30, 64, (uint8_t*) stat_string, RIGHT_MODE);
    }

    if (touch_flag) {
      process_touch(&game);
      touch_flag = 0;
    }
    if(move_flag) {
      move_boss(&game);
      move_skeletons(&game);
      move_flag = 0;
    }
    show_hero(&game);
    show_boss(&game);
    show_skeletons(&game);
    if(level_done(&game)) {
      map_init();
      game = start_game(game.level+1, game.hero.stats);
    }
  }
}

void init_timer()
{
  __HAL_RCC_TIM2_CLK_ENABLE();
  EnemyMoveTimer.Instance = TIM2;
  EnemyMoveTimer.Init.Prescaler = 10800 - 1;
  EnemyMoveTimer.Init.Period = 15000 - 1;
  EnemyMoveTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  EnemyMoveTimer.Init.CounterMode = TIM_COUNTERMODE_UP;

  HAL_TIM_Base_Init(&EnemyMoveTimer);

  HAL_NVIC_SetPriority(TIM2_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);

  HAL_TIM_Base_Start_IT(&EnemyMoveTimer);
}

void TIM2_IRQHandler()
{
  HAL_TIM_IRQHandler(&EnemyMoveTimer);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM2){
    move_flag = 1;
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
