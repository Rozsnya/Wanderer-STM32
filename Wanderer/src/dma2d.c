#include "dma2d.h"

void DMA2D_DrawImage(uint32_t data, uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
	DMA2D_HandleTypeDef hdma2d;
	uint32_t destination = LCD_FB_START_ADDRESS
			+ (x + y * BSP_LCD_GetXSize()) * 4;
	hdma2d.Instance = DMA2D;

	hdma2d.Init.Mode = DMA2D_M2M_BLEND;
	hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
	hdma2d.Init.OutputOffset = BSP_LCD_GetXSize() - width;

	// Foreground
	hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
	hdma2d.LayerCfg[1].InputOffset = 0;

	// Background
	hdma2d.LayerCfg[0].AlphaMode = DMA2D_NO_MODIF_ALPHA;
	hdma2d.LayerCfg[0].InputColorMode = DMA2D_INPUT_ARGB8888;
	hdma2d.LayerCfg[0].InputOffset = BSP_LCD_GetXSize() - width;

	HAL_DMA2D_Init(&hdma2d);
	HAL_DMA2D_ConfigLayer(&hdma2d, 1);
	HAL_DMA2D_ConfigLayer(&hdma2d, 0);
	HAL_DMA2D_BlendingStart(&hdma2d, data, destination, destination, width,
			height);
	HAL_DMA2D_PollForTransfer(&hdma2d, 10);
}
