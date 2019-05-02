#include "SystemClockConfig.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd.h"

int main(void)
{
	SystemClock_Config();

	HAL_Init();
	BSP_LCD_Init();
	BSP_LCD_LayerDefaultInit(1, LCD_FB_START_ADDRESS);
	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_TS_Init(480, 272);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(200, 130, (uint8_t*)"CSICSKA", LEFT_MODE);

	while(1){

	}
}
