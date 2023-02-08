#include "player.h"

#include <raylib.h>

#include <stdlib.h>

#include "collisions.h"

#include "main.h"

#include "common.h"

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64

#define PLAYER_ACCEL 50

#define PLAYER_DRAG_CONSTANT 6
#define PLAYER_WALL_DRAG_CONSTANT 500

#define PLAYER_DRAG_MULTIPLIER 0.05
#define PLAYER_DRAG(d) PLAYER_DRAG_CONSTANT*abs((int)player.speed.d)*PLAYER_DRAG_MULTIPLIER
#define PLAYER_WALL_DRAG(d) PLAYER_WALL_DRAG_CONSTANT*abs((int)player.speed.d)*PLAYER_DRAG_MULTIPLIER

#define PLAYER_GRAVITY 20

#define PLAYER_SPAWN_X 0
#define PLAYER_SPAWN_Y 0

//#define PLAYER_DRAG 0
//#define PLAYER_WALL_DRAG 0

Directions animation;

Player player;

//#define DEBUG

void player_debug() {
	debug(TextFormat("%f", player.debug_speed.x));
	debug(TextFormat("%f", player.debug_speed.y));
}

void player_load() {
	player.rectangle.x = PLAYER_SPAWN_X;
	player.rectangle.y = PLAYER_SPAWN_Y;

	player.rectangle.width = PLAYER_WIDTH;
	player.rectangle.height = PLAYER_HEIGHT;
	
	player.speed.x = 0;
	player.speed.y = 0;

	player.accel = PLAYER_ACCEL;
}

#define LOW_SPEED_THRESHOLD 15

bool return_if_low_speed() {
	if(
			player.speed.y > -(LOW_SPEED_THRESHOLD) &&
			player.speed.y < LOW_SPEED_THRESHOLD
	  ) {
		player.speed.y = 0;
		player.speed.x = 0;
		return true;
	} else return false;
}


void player_bounce_drag() {
	if(player.speed.x + PLAYER_WALL_DRAG(x)*dt < 0) {
		player.speed.x += PLAYER_WALL_DRAG(x)*dt;
	} else if(player.speed.x - PLAYER_WALL_DRAG(x)*dt > 0) {
		player.speed.x -= PLAYER_WALL_DRAG(x)*dt;
	} else {
		player.speed.x = 0;
	}
	if(player.speed.y + PLAYER_WALL_DRAG(y)*dt < 0) {
		player.speed.y += PLAYER_WALL_DRAG(y)*dt;
	} else if(player.speed.y - PLAYER_WALL_DRAG(y)*dt > 0) {
		player.speed.y -= PLAYER_WALL_DRAG(y)*dt;
	} else {
		player.speed.y = 0;
	}
}

void player_bounce_x() {
	player.speed.x = -(player.speed.x);
	player_bounce_drag();
}

void player_bounce_y() {
	if(return_if_low_speed()) return;
	player.speed.y = -(player.speed.y);
	player_bounce_drag();
}

void player_update() {
	player.rectangle.x += player.speed.x;
	player.rectangle.y += player.speed.y;

	if(player.speed.x + PLAYER_DRAG(x)*dt < 0) {
		player.speed.x += PLAYER_DRAG(x)*dt;
	} else if(player.speed.x - PLAYER_DRAG(x)*dt > 0) {
		player.speed.x -= PLAYER_DRAG(x)*dt;
	} else {
		player.speed.x = 0;
	}

	if(player.speed.y + PLAYER_DRAG(y)*dt < 0) {
		player.speed.y += PLAYER_DRAG(y)*dt;
	} else if(player.speed.y - PLAYER_DRAG(y)*dt > 0) {
		player.speed.y -= PLAYER_DRAG(y)*dt;
	} else {
		player.speed.y = 0;
	}

	player.speed.y += PLAYER_GRAVITY*dt;

	boxes_collision(&player);

	if(IsKeyDown(KEY_W)) {
		player.speed.y -= (float)player.accel * dt;
		animation.up = true;
	}
	if(IsKeyDown(KEY_S)) {
		player.speed.y += (float)player.accel * dt;
		animation.down = true;
	}
	if(IsKeyDown(KEY_A)) {
		player.speed.x -= (float)player.accel * dt;
		animation.left = true;
	}
	if(IsKeyDown(KEY_D)) {
		player.speed.x += (float)player.accel * dt;
		animation.right = true;
	}
}

#define PLAYER_PULSE_WIDTH 60*scale_x
#define PLAYER_PULSE_HEIGHT 20*scale_x
#define PLAYER_PULSE_DISTANCE 10*scale_x

void player_draw(float scale_x, float scale_y) {
	boxes_render();

	if(animation.right) {
		DrawRectangle(	
				player.rectangle.x - PLAYER_PULSE_WIDTH - PLAYER_PULSE_DISTANCE,
				player.rectangle.y + (float)player.rectangle.height/2 - (float)PLAYER_PULSE_HEIGHT/2,
				PLAYER_PULSE_WIDTH, PLAYER_PULSE_HEIGHT, WHITE
				);
		animation.right = false;
	}
	if(animation.left) {
		DrawRectangle(	
				player.rectangle.x + PLAYER_PULSE_DISTANCE + player.rectangle.width,
				player.rectangle.y + (float)player.rectangle.height/2 - (float)PLAYER_PULSE_HEIGHT/2,
				PLAYER_PULSE_WIDTH, PLAYER_PULSE_HEIGHT, WHITE
				);
		animation.left = false;
	}
	if(animation.up) {
		DrawRectangle(	
				player.rectangle.x + (float)player.rectangle.width/2 - (float)PLAYER_PULSE_HEIGHT/2,
				player.rectangle.y + player.rectangle.width + PLAYER_PULSE_DISTANCE,
				PLAYER_PULSE_HEIGHT, PLAYER_PULSE_WIDTH, WHITE
				);
		animation.up = false;
	}
	if(animation.down) {
		DrawRectangle(	
				player.rectangle.x + (float)player.rectangle.width/2 - (float)PLAYER_PULSE_HEIGHT/2,
				player.rectangle.y - PLAYER_PULSE_WIDTH - PLAYER_PULSE_DISTANCE,
				PLAYER_PULSE_HEIGHT, PLAYER_PULSE_WIDTH, WHITE
				);
		animation.down = false;
	}

	DrawRectangleRec(player.rectangle, WHITE);
}
