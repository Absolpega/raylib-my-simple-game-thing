#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <raylib.h>

#include "player.h"

#define MAP_WIDTH 4000
#define MAP_HEIGHT 4000

void boxes_collision(Player *player);

void boxes_render();

enum direction get_collided_side_of_rectangle(Player *player, Rectangle *rectangle);

#endif
