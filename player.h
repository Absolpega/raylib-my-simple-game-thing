#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

void player_bounce_x();	
void player_bounce_y();	

typedef struct {
	bool up;
	bool down;
	bool left;
	bool right;
} Directions;

typedef struct {
	float accel;
	bool standing;
	Vector2 speed;
	Vector2 debug_speed;
	Rectangle rectangle;
} Player;

enum direction {
		nodirection,
		up,
		down,
		left,
		right,
};

extern Player player;

void player_debug();

void player_load();

void player_update();

void player_draw(float scale_x, float scale_y);

#endif
