#include "collisions.h"

#include <raylib.h>

#include "player.h"

#include "colors.h"

Rectangle boxes[] = {
	{
		200,
		MAP_HEIGHT - 300,
		50,
		60,
	},
	{
		900,
		700,
		100,
		20,
	},
	{
		1000,
		700,
		20,
		100,
	},
	{
		3000,
		1400,
		600,
		40,
	},
};

int boxes_lenght = sizeof(boxes)/sizeof(boxes[0]);

void boxes_render() {
	for(int i = 0; i < boxes_lenght; i++) {
		DrawRectangle(boxes[i].x, boxes[i].y, boxes[i].width, boxes[i].height, COLOR_BOXES);
	}
}

enum direction get_collided_side_of_rectangle(Player *player, Rectangle *rectangle) {
	
	Rectangle result = GetCollisionRec(player->rectangle, *rectangle);

	if(result.width > result.height) {
		// down or up
#define COLLSION_MARGIN_TOP 0
		if(player->rectangle.y < rectangle->y + COLLSION_MARGIN_TOP) {
			return up;
		} else {
			return down;
		}
	} else if(result.width < result.height) {
		// left or right
		if(player->rectangle.x < rectangle->x) {
			return left;
		} else {
			return right;
		}
	}

	return nodirection;
}

bool boxes_collision(Player *player) {
	if(player->rectangle.x < 0) {
		player->rectangle.x = 0;
		player_bounce_x();
	} else if(player->rectangle.x > MAP_WIDTH - player->rectangle.width) {
		player->rectangle.x = MAP_WIDTH - player->rectangle.width;
		player_bounce_x();
	}

	if(player->rectangle.y < 0) {
		player->rectangle.y = 0;
		player_bounce_y();	
	} else if(player->rectangle.y >= MAP_HEIGHT - player->rectangle.height) {
		player->rectangle.y = MAP_HEIGHT - player->rectangle.height + 1;
		player_bounce_y();	
		return true;
	}

	for(int i = 0; i < boxes_lenght; i++) {
		switch(get_collided_side_of_rectangle(player, &boxes[i])) {
			case up:
				player->rectangle.y = boxes[i].y - player->rectangle.height + 1;
				player_bounce_y();
				return true;
				break;
			case down:
				player->rectangle.y = boxes[i].y + boxes[i].height;
				player_bounce_y();
				break;
			case left:
				player->rectangle.x = boxes[i].x - player->rectangle.width;
				player_bounce_x();
				break;
			case right:
				player->rectangle.x = boxes[i].x + boxes[i].width;
				player_bounce_x();
				break;
			case nodirection:
				break;
		}
	}
	return false;
}
