//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_player_H
#define METASPRITE_player_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define player_TILE_ORIGIN 0
#define player_TILE_H 8
#define player_WIDTH 16
#define player_HEIGHT 16
#define player_TILE_COUNT 3
#define player_PIVOT_X 8
#define player_PIVOT_Y 8
#define player_PIVOT_W 16
#define player_PIVOT_H 16

BANKREF_EXTERN(player)

extern const palette_color_t player_palettes[4];
extern const uint8_t player_tiles[48];

extern const metasprite_t* const player_metasprites[1];

#endif