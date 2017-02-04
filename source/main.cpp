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
#include <hbkb.h>
#include <menu.h>

#define _GLIBCXX_USE_CXX11_ABI 0/1


int main()
{
	// Allows to take inputs (Specifically the start button for our case)
    hidInit();
	
    //Tells us when a key is pressed down
    u32 kDown;
	u32 kHeld;
	u8 KBState;
	touchPosition touch;
	std::string InputHBKB = " ";
	sf2d_init();
	sf2d_set_clear_color(RGBA8(200, 200, 200, 0xFF));
	sf2d_set_vblank_wait(0);

	// Font loading
	sftd_init();
	HB_Keyboard sHBKB;
	sftd_font *font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);
	//char *sansFont = "../data/FreeSans.tff";
	//sftd_font *font = sftd_load_font_file(sansFont);
	
	//32-bit processor
	std::bitset<8> gameStatus; 
	
	/* 
	//http://www.cplusplus.com/reference/bitset/bitset/set/
	{0, // if 0, draw on bottom screen. if 1, top screen
	0, // if 0, no keyboard. if 1, keyboard
	0, 
	0, 
	0, //if 0, not in stats mode. if 1, stats mode.
	0, // if 0, in off-stream mode. if 1, in on-stream mode
	0, //if 0, not in save menu. if 1, in save menu
	0, // if 0, main menu. if 1, in game
	} 
	*/
	
	// Main loop
	
	while (aptMainLoop())
	{

		hidScanInput();
		kDown = hidKeysDown();
		kHeld = hidKeysHeld();
		
		//Read the touch screen coordinates
		hidTouchRead(&touch);
		
		if(!gameStatus[0]) {
			if(kDown & KEY_SELECT) {
				if(gameStatus.any()) { //Return to start menu
					gameStatus = gameStatus << 8;
				}
					
				if(gameStatus.none()) { //Quit game
					break;
				}
			}
		}
		if (kDown & (KEY_START || KEY_A)) {
			gameStatus[0] = 1;
		} else if(kDown & KEY_B) {
			gameStatus[6] = ~gameStatus[6];
		}
			
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			cxsimulator::render(touch, gameStatus, InputHBKB, kDown, sHBKB, font);
		sf2d_end_frame();
		
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			cxsimulator::render(touch, gameStatus, InputHBKB, kDown, sHBKB, font);
		sf2d_end_frame();
		
		sf2d_swapbuffers();
	}
	
	sftd_free_font(font);
	sftd_fini();
	sf2d_fini();
	hidExit();
	
	return 0;
}
