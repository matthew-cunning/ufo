#include <gb/gb.h>
#include <gb/metasprites.h>

#include <stdio.h>
#include <stdlib.h>

#include "../headers/define.h"
#include "../headers/player_utils.h"

#include "../graphics/gameplay/player.h"
#include "../graphics/gameplay/player_actions.h"

uint8_t gameplay(void) {

    // Make background blank
    fill_bkg_rect(0,0,20,18,0);

    // Draw Player sprite [2x2 metasprite]:
    // Load the player sprite data into VRAM
    set_sprite_data(TILE_NUM_START, sizeof(player_tiles) >> 4, player_tiles);
    set_sprite_data(PLAYER_ACTION_TILE_START, 5, player_actions);

    // Set shot sprite
    set_sprite_tile(SPRITE_ID_SHOT_L,TILE_SHOT_L);
    set_sprite_tile(SPRITE_ID_SHOT_R,TILE_SHOT_R);
    set_sprite_tile(SPRITE_ID_TRACTOR,TILE_TRACTOR);

    // Test: Move shot sprite to 80,80 (get rid of this later ? )
    move_sprite(SPRITE_ID_SHOT_L,0,SHOT_OFFSCREEN_Y);
    move_sprite(SPRITE_ID_SHOT_R,0,SHOT_OFFSCREEN_Y);

    move_sprite(SPRITE_ID_TRACTOR,0,SHOT_OFFSCREEN_Y);
    // Init the player metasprite
    init_player();

    // Check for input, move player character
    while(1) {
        move_player();
        shoot();
        grab();
        // Wait for vertical blank refresh - update the game's visuals 
        wait_vbl_done();
    }
}