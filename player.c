#include "player.h"

#include <raylib.h>
#include <raymath.h>

#include <stdlib.h>

#include "collisions.h"

#include "main.h"

#include "common.h"

#include "colors.h"

#define PLAYER_WIDTH 64
#define PLAYER_HEIGHT 64

#define PLAYER_ACCEL 1000
#define PLAYER_JUMP 50
#define PLAYER_DASH 150

#define PLAYER_DRAG_CONSTANT 60
#define PLAYER_WALL_DRAG_CONSTANT 500

#define PLAYER_DRAG_MULTIPLIER 0.05
#define PLAYER_DRAG(d) PLAYER_DRAG_CONSTANT*abs((int)player.speed.d)*PLAYER_DRAG_MULTIPLIER
#define PLAYER_WALL_DRAG(d) PLAYER_WALL_DRAG_CONSTANT*abs((int)player.speed.d)*PLAYER_DRAG_MULTIPLIER

#define PLAYER_GRAVITY 200

#define PLAYER_SPAWN_X 0
#define PLAYER_SPAWN_Y 0

#define DT_SLOWDOWN 0.05

Directions animation;

Player player;

Vector2 get_relative(Rectangle rectX, Vector2 rectY) {
	return (Vector2){
		rectY.x - rectX.x,
		rectY.y - rectX.y,
	};
}

void player_debug() {
	//Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), camera);
	//Vector2 relative = get_relative(player.rectangle, mouse_position);
	//Vector2 normalized = Vector2Normalize(relative);

	//debug(TextFormat("%f", player.rectangle.x));
	//debug(TextFormat("%f", player.rectangle.y));
	//debug(" ");
	debug(TextFormat("%f", player.debug_speed.x));
	debug(TextFormat("%f", player.debug_speed.y));
	debug(" ");
	debug(TextFormat("%b", player.standing));
	//debug(" ");
	//debug(TextFormat("%f", mouse_position.x));
	//debug(TextFormat("%f", mouse_position.y));
	//debug(" ");
	//debug(TextFormat("%f", relative.x));
	//debug(TextFormat("%f", relative.y));
	//debug(" ");
	//debug(TextFormat("%f", normalized.x));
	//debug(TextFormat("%f", normalized.y));
}

void player_load() {
	player.rectangle.x = PLAYER_SPAWN_X;
	player.rectangle.y = PLAYER_SPAWN_Y;

	player.rectangle.width = PLAYER_WIDTH;
	player.rectangle.height = PLAYER_HEIGHT;
	
	player.speed.x = 0;
	player.speed.y = 0;

	player.accel = PLAYER_ACCEL;

	player.standing = false;
}

#define LOW_SPEED_THRESHOLD 200

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

	player.in_slowdown = false;
	if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		dt *= DT_SLOWDOWN;
		player.rectangle.x += player.speed.x * DT_SLOWDOWN;
		player.rectangle.y += player.speed.y * DT_SLOWDOWN;
		player.in_slowdown = true;
	} else {
		player.rectangle.x += player.speed.x;
		player.rectangle.y += player.speed.y;
	}

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

	if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		Vector2 mouse_position = GetScreenToWorld2D(GetMousePosition(), camera);
		Vector2 relative = get_relative(player.rectangle, mouse_position);
		Vector2 normalized = Vector2Normalize(relative);
		Vector2 scaled = Vector2Scale(normalized, PLAYER_DASH);
		player.speed = Vector2Add(player.speed, scaled);
	}

	if(boxes_collision(&player)) {
		player.standing = true;
	}

	if(IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)) {
		if(player.standing)
			player.speed.y -= PLAYER_JUMP;
	}
	//if(IsKeyDown(KEY_S)) {
	//	player.speed.y += player.accel * dt;
	//	animation.down = true;
	//}
	if(IsKeyDown(KEY_A)) {
		player.rectangle.x -= player.accel * dt;
	}
	if(IsKeyDown(KEY_D)) {
		player.rectangle.x += player.accel * dt;
	}
}

#define PLAYER_PULSE_WIDTH		60
#define PLAYER_PULSE_HEIGHT		20
#define PLAYER_PULSE_DISTANCE	10

Image		slowdown_image;
Texture2D	slowdown_texture;

bool has_resized = false;

void player_draw(float scale_x, float scale_y) {
	boxes_render();

	//if(animation.right) {
	//	DrawRectangle(	
	//			player.rectangle.x - PLAYER_PULSE_WIDTH - PLAYER_PULSE_DISTANCE,
	//			player.rectangle.y + (float)player.rectangle.height/2 - (float)PLAYER_PULSE_HEIGHT/2,
	//			PLAYER_PULSE_WIDTH, PLAYER_PULSE_HEIGHT, COLOR_PULSE
	//			);
	//	animation.right = false;
	//}
	//if(animation.left) {
	//	DrawRectangle(	
	//			player.rectangle.x + PLAYER_PULSE_DISTANCE + player.rectangle.width,
	//			player.rectangle.y + (float)player.rectangle.height/2 - (float)PLAYER_PULSE_HEIGHT/2,
	//			PLAYER_PULSE_WIDTH, PLAYER_PULSE_HEIGHT, COLOR_PULSE
	//			);
	//	animation.left = false;
	//}
	//if(animation.up) {
	//	DrawRectangle(	
	//			player.rectangle.x + (float)player.rectangle.width/2 - (float)PLAYER_PULSE_HEIGHT/2,
	//			player.rectangle.y + player.rectangle.width + PLAYER_PULSE_DISTANCE,
	//			PLAYER_PULSE_HEIGHT, PLAYER_PULSE_WIDTH, COLOR_PULSE
	//			);
	//	animation.up = false;
	//}
	//if(animation.down) {
	//	DrawRectangle(	
	//			player.rectangle.x + (float)player.rectangle.width/2 - (float)PLAYER_PULSE_HEIGHT/2,
	//			player.rectangle.y - PLAYER_PULSE_WIDTH - PLAYER_PULSE_DISTANCE,
	//			PLAYER_PULSE_HEIGHT, PLAYER_PULSE_WIDTH, COLOR_PULSE
	//			);
	//	animation.down = false;
	//}

	if(IsWindowResized())
		has_resized = true;

	if(player.in_slowdown) {
		if(has_resized) {
			slowdown_image = GenImageGradientRadial(
					GetScreenWidth(),
					GetScreenHeight(),
					-1,
					(Color) {0,0,0,0},
					(Color) {0,0,0,180}
					);
			slowdown_texture = LoadTextureFromImage(slowdown_image);
			has_resized = false;
		}

		EndMode2D();
		DrawTexture(
				slowdown_texture,
				0,0,
				(Color) {0,0,0,255}
				);
		BeginMode2D(camera);
	}

	DrawRectangleRec(player.rectangle, COLOR_PLAYER);
}
