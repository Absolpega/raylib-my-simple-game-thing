#include "common.h"

#include <raylib.h>

#include "main.h"

int debug_y;

#define DEBUG_SPACING 5
void debug(const char *text) {
	DrawText(text, GetScreenWidth() - MeasureText(text, 20) - DEBUG_SPACING, debug_y, 20, WHITE);
	debug_y += 20 + DEBUG_SPACING;
}

void CustomDrawFPS(int posX, int posY)
{
    Color color = LIME;                         // Good FPS
    int fps = GetFPS();

    if ((fps < 30) && (fps >= 15)) color = ORANGE;  // Warning FPS
    else if (fps < 15) color = RED;             // Low FPS

    DrawText(TextFormat("%2i", GetFPS()), posX, posY, 20, color);
}
