#include <gb/gb.h>
#include <stdlib.h>

void gb_turn_on () {
    DISPLAY_ON;
    SHOW_BKG;
    SHOW_SPRITES;
    // IMPORTANT: SET SPRITE MODE TO 8x8 FIRST TO ENSURE COMPATIBILITY WITH THE PLAYER SPRITE
    SPRITES_8x8;
}