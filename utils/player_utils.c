#include <gb/gb.h>
#include <stdio.h>

#include "../graphics/gameplay/player.h"
#include "../headers/define.h"
#include "../headers/common.h"

#include "../graphics/gameplay/player_actions.h"

#include <gb/metasprites.h>

typedef struct Shot {
    int16_t x;
    int16_t y;
} Shot;

Shot shot_l, shot_r;

void init_player() {

    // default: player faces right;
    facing_right = 1;
    player_x = 0 << 4;
    player_y = 144 << 4;
    player_top_speed = 20;
    player_responsiveness_x = 2;
    player_responsiveness_y = 4;

    shot_ready = 1;
    shot_speed = 3;

    // Duration to wait in between shots (n/60)
    shot_timer = 30;

    // set shot counter to 0
    shot_counter = 0;

    tractor_anim_counter=0;
    tractor_anim_index=0;
    // Move player to X, Y
    move_metasprite(player_metasprites[0], TILE_NUM_START, SPRITE_NUM_START, (player_x + (X_OFFSET << 4))>>4, (player_y + (Y_OFFSET << 4))>>4);
}
void move_player() {
    // Reset button pressed
    button_pressed = 0;


    // Allow movement while holding down multiple directions
    /*
        What's with the |= ?
        Efficient way of doing logic to check if a button in the X or Y axis is pressed.

        As an example, for the X axis...
        00 | 01 == 01 
        Therefore if X_AXIS is pressed down, button_pressed will be set to 01
        This is important for the section which follows where we want to reduce the sprite's speed 
        when no buttons are pressed in those axis directions.
    */
    if (joypad() & J_UP) { 
        player_velocity_y -= 2;
        if(player_velocity_y < -player_top_speed) player_velocity_y = -player_top_speed;
        button_pressed |= Y_AXIS_PRESSED; 
    }
    else if (joypad() & J_DOWN) {
        player_velocity_y +=2;
        if(player_velocity_y > player_top_speed) player_velocity_y = player_top_speed;
        button_pressed |= Y_AXIS_PRESSED; 
    }

    if (joypad() & J_LEFT) {
        facing_right = 0;
        player_velocity_x -=2;
        if(player_velocity_x < -player_top_speed) player_velocity_x = -player_top_speed;
        button_pressed |= X_AXIS_PRESSED; 
    }
    else if (joypad() & J_RIGHT) {
        facing_right = 1;
        player_velocity_x +=2;
        if(player_velocity_x > player_top_speed) player_velocity_x = player_top_speed;
        button_pressed |= X_AXIS_PRESSED; 
    }


    player_x += player_velocity_x;
    player_y += player_velocity_y;

    // Clamp to X boundaries of screen
    if((player_x>>4) <= X_LIMIT_LOWER) player_x=X_LIMIT_LOWER;
    else if((player_x>>4) >= X_LIMIT_UPPER-X_OFFSET) { player_x=(X_LIMIT_UPPER-X_OFFSET)<<4; player_velocity_x = 0; }

    // Clamp to Y boundaries of screen
    if((player_y>>4) <= Y_LIMIT_LOWER+16) player_y=Y_LIMIT_LOWER+(16<<4);
    else if((player_y>>4) >= Y_LIMIT_UPPER) { player_y=Y_LIMIT_UPPER<<4; player_velocity_y = 0; }


    // Flip the player sprite depending on what direction player presses
    facing_right ? move_metasprite(player_metasprites[0], TILE_NUM_START, SPRITE_NUM_START, (player_x>>4)+X_OFFSET, (player_y>>4)+Y_OFFSET)
    : move_metasprite_vflip(player_metasprites[0], TILE_NUM_START, SPRITE_NUM_START, (player_x>>4)+X_OFFSET, (player_y>>4)+Y_OFFSET);

    // This section must come after the move_metasprite so that move_metasprite affects the change in velocity
    // Which occurs immediately after a button is pressed.

    /*
        How this works is as follows:
        If X axis is pressed, button_pressed will be 01.
        If no button is pressed, button_pressed will be 00.   
        Remember the difference between logical AND and bitwise AND...

        Compare button_pressed against X_AXIS_PRESSED...
        Pressed:
        (01 & (bitwise) 01) == 01 
        Not 0, so TRUE

        Not pressed:
        (00 & (bitwise) 01) == 00
        Remember: 0 is FALSE 

        if(!(expr)) -- Logical NOT (!) asks the question:
        Does expr evaluate to false?
        If it does evaluate to false, execute the block of code.
        
        */

    // Reduce speed on X axis
    // If a button on X_AXIS isn't pressed, execute this code 
    if (!(button_pressed & X_AXIS_PRESSED))  {
        if (player_velocity_x != 0)
            if(player_velocity_x > 0) player_velocity_x--;
            else player_velocity_x++;
    }

    // Reduce speed on Y axis
    // If a button on Y_AXIS isn't pressed, execute this code 
    if (!(button_pressed & Y_AXIS_PRESSED))  {
        if (player_velocity_y != 0)
            if(player_velocity_y > 0) player_velocity_y--;
            else player_velocity_y++;
    }
}

void grab() {
    // Spawn tractor beam sprite below ufo
    if (joypad() & J_A) {
        move_sprite(SPRITE_ID_TRACTOR,(player_x>>4) + 12,(player_y>>4) + 16);
        tractor_anim_counter++;
        if(tractor_anim_counter >= 10) {
            tractor_anim_counter = 0;
            set_sprite_tile(SPRITE_ID_TRACTOR,TILE_TRACTOR + (++tractor_anim_index % 3));

        }
    }

    else {
        move_sprite(SPRITE_ID_TRACTOR,0,SHOT_OFFSCREEN_Y);
        set_sprite_tile(SPRITE_ID_TRACTOR,TILE_TRACTOR);
    }
}

void shoot() {

    if(!shot_ready && shot_counter < shot_timer)
        shot_counter++;

    if(!shot_ready && shot_counter >= shot_timer && (shot_l.y >= SHOT_OFFSCREEN_Y || shot_r.y >= SHOT_OFFSCREEN_Y)) {
        shot_ready = 1;
        shot_counter = 0;
    }

    // Shoot out diagonal beams from center of ufo
    if ((joypad() & J_B ) && shot_ready){
        shot_ready = 0;
        shot_l.x = player_x>>4; 
        shot_l.y = (player_y>>4)+16; 

        shot_r.x = (player_x>>4) + SHOT_X_OFFSET + 8;
        shot_r.y = (player_y>>4)+16;
        move_sprite(SPRITE_ID_SHOT_L,shot_l.x,shot_l.y);
        move_sprite(SPRITE_ID_SHOT_R,shot_r.x,shot_r.y);
        button_pressed |= B_PRESSED;
    }

    if(!(button_pressed & B_PRESSED) && !shot_ready) {

        // TODO: Fix shots wrapping around from upper corners ( address the logic in if statements...)
        if(shot_l.x > SHOT_OFFSCREEN_X_NEG  || shot_l.y < SHOT_OFFSCREEN_Y ) {
            shot_l.x-=shot_speed;
            shot_l.y+=shot_speed;
            move_sprite(SPRITE_ID_SHOT_L,shot_l.x,shot_l.y);
        }
        else { shot_r.x = 0; shot_l.y=SHOT_OFFSCREEN_Y; }

        if(shot_r.x < SHOT_OFFSCREEN_X_POS  || shot_r.y < SHOT_OFFSCREEN_Y ) {
            shot_r.x+=shot_speed;
            shot_r.y+=shot_speed;
            move_sprite(SPRITE_ID_SHOT_R,shot_r.x,shot_r.y);
        }
        else { shot_r.x = 0; shot_r.y=SHOT_OFFSCREEN_Y; }
    }

}