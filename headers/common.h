#include <gb/gb.h>

int16_t player_x, player_y;

// Movement stuff
int16_t player_velocity_x, player_velocity_y;
uint8_t player_responsiveness_x, player_responsiveness_y;
int8_t player_top_speed;

uint8_t facing_right;

// Shooting stuff
uint8_t shot_counter;
int16_t shot_x, shot_y;
uint8_t b_down, a_down;
uint8_t shot_ready;
uint8_t shot_speed;
uint8_t shot_timer;

uint8_t tractor_anim_counter;
uint8_t tractor_anim_index;
// For comparing what button is currently pressed with bitwise logic
uint8_t button_pressed;

