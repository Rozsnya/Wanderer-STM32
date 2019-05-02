#include "SystemClockConfig.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"
#include "utility.h"
#include "map.h"
#include "dma2d.h"
#include "images.h"

int main(void) {

	HAL_Init();
	SystemClock_Config();
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_TS_Init(480, 272);
	map_init();

	DMA2D_DrawImage(HERO_UP_DATA, 105, 1, 27, 27);
  DMA2D_DrawImage(HERO_RIGHT_DATA, 132, 1, 27, 27);
  DMA2D_DrawImage(HERO_DOWN_DATA, 105, 28, 27, 27);
  DMA2D_DrawImage(HERO_LEFT_DATA, 132, 28, 27, 27);
  DMA2D_DrawImage(SKELETON_DATA, 105, 244, 27, 27);
  DMA2D_DrawImage(BOSS_DATA, 348, 244, 27, 27);

	while (1) {

	}
}


