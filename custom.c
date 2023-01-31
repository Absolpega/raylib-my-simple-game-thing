#include "custom.h"

#include <raylib.h>

void CustomDrawFPS(int posX, int posY)
{
    Color color = LIME;                         // Good FPS
    int fps = GetFPS();

    if ((fps < 30) && (fps >= 15)) color = ORANGE;  // Warning FPS
    else if (fps < 15) color = RED;             // Low FPS

    DrawText(TextFormat("%2i", GetFPS()), posX, posY, 20, color);
}
