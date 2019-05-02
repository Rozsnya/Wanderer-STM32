#ifndef DMA2D_H_
#define DMA2D_H_
#include <stdint.h>
#include "stm32746g_discovery_lcd.h"

void DMA2D_DrawImage(uint32_t data, uint32_t x, uint32_t y, uint32_t width, uint32_t height);



#endif /* DMA2D_H_ */
