#include "main.h"

#include <raylib.h>

#include "common.h"

#include "player.h"

#include "collisions.h"

#include "colors.h"

#include "timers.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define UI_PADDING 10

Font font;

Camera2D camera;

float dt = 0.0;
float scale_x = 1.0;
float scale_y = 1.0;

void camera_update() {
	camera.offset.x	= (float)GetScreenWidth()/2;
	camera.offset.y	= (float)GetScreenHeight()/2;
	camera.target.x	= player.rectangle.x + player.rectangle.width/2;
	camera.target.y	= player.rectangle.y + player.rectangle.height/2;
}

int main() {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib thing");

	font = GetFontDefault();

	HideCursor();
	
	camera.rotation	= 0;
	camera.zoom		= 0.5;

	player_load();

	while(!WindowShouldClose()) {
		update();
		draw();
	}

	CloseWindow();

	return 0;
}

void update() {
	player_update();
	timers_update();
}

void draw() {
	BeginDrawing();
	debug_y = UI_PADDING;
	camera_update();
	BeginMode2D(camera);
	dt = GetFrameTime();

	ClearBackground(BLACK);
	//DrawRectangle(0,0,MAP_WIDTH, MAP_HEIGHT, COLOR_SKY);
	DrawRectangleGradientV(0,0,MAP_WIDTH, MAP_HEIGHT, COLOR_SKY_UPPER, COLOR_SKY_LOWER);
	player_draw(scale_x, scale_y);

	EndMode2D();
	
	CustomDrawFPS(GetScreenWidth() - UI_PADDING - MeasureText(TextFormat("%2i", GetFPS()), 20), debug_y);
	debug_y += 20 + UI_PADDING;


	player_debug();

#define CURSOR_RADIUS 3
	if(IsCursorOnScreen())
		DrawCircle(GetMouseX(), GetMouseY(), CURSOR_RADIUS, LIGHTGRAY);

	EndDrawing();
}


