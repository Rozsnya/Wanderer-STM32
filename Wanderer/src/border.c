#include "border.h"

void draw_arrow_keys(){
  DMA2D_DrawImage((uint32_t)ARROW_UP_DATA, 27, 150, 50, 50);
  DMA2D_DrawImage((uint32_t)ARROW_DOWN_DATA, 27, 200, 50, 50);
  DMA2D_DrawImage((uint32_t)ARROW_LEFT_DATA, 377, 175, 50, 50);
  DMA2D_DrawImage((uint32_t)ARROW_RIGHT_DATA, 428, 175, 50, 50);
}

void draw_icons(){
  //hero stats
  DMA2D_DrawImage((uint32_t)HEART_DATA, 0, 1, 27, 27);
  DMA2D_DrawImage((uint32_t)SWORD_DATA, 0, 28, 27, 27);
  DMA2D_DrawImage((uint32_t)SHIELD_DATA, 0, 55, 27, 27);

  //enemy stats
  DMA2D_DrawImage((uint32_t)HEART_DATA, 453, 1, 27, 27);
  DMA2D_DrawImage((uint32_t)SWORD_DATA, 453, 28, 27, 27);
  DMA2D_DrawImage((uint32_t)SHIELD_DATA, 453, 55, 27, 27);
}
