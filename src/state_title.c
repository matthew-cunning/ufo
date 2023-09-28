#include <gb/gb.h>
#include "../headers/define.h"
#include "../graphics/title/title_data.c"
#include "../graphics/title/title_map.c"

uint8_t title(void) {
    set_bkg_data(BKG_NUM_START, 179, title_data); 
    set_bkg_tiles(0,0,20,18,title_map);
    while(1) {
        if(joypad() & (J_START | J_A))
            return STATE_GAMEPLAY;
    }

}
