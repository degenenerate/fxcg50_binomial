#include "../include/background.h"

void draw_background()
{
    VRAM_CopySprite(BACKGROUND_SPRITE, 0, 0, 384, 216);
}
