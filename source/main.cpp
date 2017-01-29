#include <stdio.h>
#include <iostream>
#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include "FreeSans_ttf.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <bitset>

int main()
{
    // Allows to take inputs (Specifically the start button for our case)
    hidInit();

    //Tells us when a key is pressed down
    u32 kDown;
	u32 kHeld;

	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	sf2d_set_vblank_wait(0);

	// Font loading
	sftd_init();
	consoleInit(GFX_BOTTOM,NULL);
	sftd_font *font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);
	//char *sansFont = "../data/FreeSans.tff";
	//sftd_font *font = sftd_load_font_file(sansFont);
	
	//32-bit processor
	std::bitset<4> gameStatus; 
	/* 
	//http://www.cplusplus.com/reference/bitset/bitset/set/
	{0, //if 0, not in stats mode. if 1, stats mode.
	0, // if 0, in off-stream mode. if 1, in on-stream mode
	0, //if 0, not in save menu. if 1, in save menu
	0 } // if 0, main menu. if 1, in game
	*/
	
	// Main loop
	
	while (aptMainLoop())
	{
		hidScanInput();
		kDown = hidKeysDown();
		kHeld = hidKeysHeld();
		
		sf2d_start_frame(GFX_TOP, GFX_LEFT);	
		if (kDown & KEY_START || KEY_A) {
			gameStatus[0] = ~gameStatus[0];

			if(gameStatus[0]) {
				std::cout << "Unpaused game" << std::endl;
			} else {
				std::cout << "Paused game" << std::endl;
			}
		}		
		
			sftd_draw_textf(font, 10, 10, RGBA8(0, 255, 0, 255), 20, "FPS %f", sf2d_get_fps());

		
		if(kDown & KEY_SELECT) {
			if(gameStatus.any()) {
				gameStatus = gameStatus << 4;
			}
			
			sftd_draw_textf(font, 10, 10, RGBA8(0, 255, 0, 255), 20, "FPS %f", sf2d_get_fps());
			std::cout << gameStatus << std::endl;
		}
	
				
		//sftd_draw_textf(font, 10, 10, RGBA8(0, 255, 0, 255), 20, "FPS %f", sf2d_get_fps());
		sf2d_end_frame();
		sf2d_swapbuffers();
	}

	//gfxExit();
	return 0;
}
