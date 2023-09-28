REM Delete the old .gb ROM
del gb_jam_space.gb

REM Run png2asset to generate C source file assets from the PNGs 
@REM ..\..\bin\png2asset .\graphics\title.png -spr8x8 -c .\graphics\title\title.c 
..\..\bin\png2asset .\graphics\player.png -spr8x8 -c .\graphics\gameplay\player.c 
@REM ..\..\bin\png2asset .\graphics\player_actions.png -spr8x8 -sw 8 -sh 8 -c .\graphics\gameplay\player_actions.c 

REM Compile and link the C source files into .gb ROM
..\..\bin\lcc  -o gb_jam_space.gb src/*.c graphics/gameplay/*.c utils/*.c

REM Run the compiled ROM
gb_jam_space.gb

