#include "timers.h"

#include "main.h"

#include "player.h"

#define TIMER_ONE_SECOND_LENGHT 1
float timer_one_second;

#define TIMER_TENTH_SECOND_LENGHT 0.1
float timer_tenth_second;

#define TIMER_HUNDREDTH_SECOND_LENGHT 0.01
float timer_hundredth_second;

void timer_one_second_callback() {
}

void timer_tenth_second_callback() {
	player.standing = false;
	player.debug_speed = player.speed;
}

void timer_hundredth_second_callback() {
}

void timers_update() {
	timer_one_second		+= dt;
	timer_tenth_second		+= dt;
	timer_hundredth_second	+= dt;

	while(timer_one_second > TIMER_ONE_SECOND_LENGHT) {
		timer_one_second -= TIMER_ONE_SECOND_LENGHT;
		timer_one_second_callback();
	}
	while(timer_tenth_second > TIMER_TENTH_SECOND_LENGHT) {
		timer_tenth_second -= TIMER_TENTH_SECOND_LENGHT;
		timer_tenth_second_callback();
	}
	while(timer_hundredth_second > TIMER_HUNDREDTH_SECOND_LENGHT) {
		timer_hundredth_second -= TIMER_HUNDREDTH_SECOND_LENGHT;
		timer_one_second_callback();
	}
}
