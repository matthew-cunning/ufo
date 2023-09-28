#define STATE_TITLE 1
#define STATE_GAMEPLAY 2
#define STATE_GAME_OVER 3

#define SCREEN_INDEX_MAX_X 20
#define SCREEN_INDEX_MAX_Y 18 

#define BKG_NUM_START 0

#define SPRITE_NUM_START 0
#define TILE_NUM_START 0
#define PLAYER_ACTION_TILE_START 3

#define DOWNSHIFT_MOVEMENT 4

// Sprite IDs 0-3 used by player metasprite
#define SPRITE_ID_SHOT_L 4
#define SPRITE_ID_SHOT_R 5
#define SPRITE_ID_TRACTOR 6

// Sprite tile in VRAM of player shot is 3
#define TILE_SHOT_L 3
#define TILE_SHOT_R 4
#define TILE_TRACTOR 5

#define X_AXIS_PRESSED 1
#define Y_AXIS_PRESSED 2

#define A_PRESSED 3
#define B_PRESSED 4

#define X_OFFSET 16 
#define Y_OFFSET 8 

#define SHOT_X_OFFSET 16
#define SHOT_Y_OFFSET 16

#define X_LIMIT_LOWER 0
#define Y_LIMIT_LOWER 0

#define X_LIMIT_UPPER 160
#define Y_LIMIT_UPPER 144

#define SHOT_OFFSCREEN_Y 160
#define SHOT_OFFSCREEN_X_POS 176
#define SHOT_OFFSCREEN_X_NEG -16 
