#include <gb/gb.h>
#include <gb/metasprites.h>

#include <stdio.h>
#include <stdlib.h>


#include "../headers/gb_sys.h"
#include "../headers/define.h"
#include "../headers/player_utils.h"
#include "../headers/states.h"


void main (void) {

    uint8_t current_state;
    // Turn on GB
    gb_turn_on();
 
    // TODO: Draw background


    current_state = STATE_TITLE;
    // current_state = STATE_GAMEPLAY;


    // Main game loop
    while (1) {
        switch (current_state) {
            case STATE_TITLE:
                // Call Title function
                current_state = (current_state = title()) > 0 ? current_state : STATE_TITLE;
                // current_state = title()
                break;
            case STATE_GAMEPLAY:
                // Call Gameplay function, only change state if it doesn't return 0
                current_state = (current_state = gameplay()) > 0 ? current_state : STATE_GAMEPLAY;
                break;
            case STATE_GAME_OVER:
                // Call Gameplay function
                break;

            default:
                // Call TItle function
                break;
        }
    }
    

}