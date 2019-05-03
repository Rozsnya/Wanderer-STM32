#include "border.h"

void draw_arrow_keys(){
  DMA2D_DrawImage((uint32_t)ARROW_UP_DATA, 27, 150, 50, 50);
  DMA2D_DrawImage((uint32_t)ARROW_DOWN_DATA, 27, 200, 50, 50);
  DMA2D_DrawImage((uint32_t)ARROW_LEFT_DATA, 377, 175, 50, 50);
  DMA2D_DrawImage((uint32_t)ARROW_RIGHT_DATA, 428, 175, 50, 50);
}
