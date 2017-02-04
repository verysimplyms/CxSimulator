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

namespace cxsimulator {
		void render(touchPosition &touch, std::bitset<8> &gameStatus, std::string &InputHBKB, u32 &kDown, HB_Keyboard &sHBKB, sftd_font *font) {
				if(!gameStatus[7]) { //top screen
					sftd_draw_textf(font, 10, 10, RGBA8(0, 255, 0, 255), 10, "FPS %f", sf2d_get_fps());
					if(gameStatus[6]) {
						sftd_draw_textf(font, 10, 30, RGBA8(0, 255, 0, 255), 20, "Input: %s", InputHBKB.c_str());
					} else {
						sftd_draw_textf(font, 160, 120, RGBA8(0, 255, 0, 255), 20, "CX Simulator");
					}
				} else if(gameStatus[7]) {
					// bottom screen
					if(gameStatus[0]){		
						if(gameStatus[6]) {
							cxsimulator::keyboardCalling(sHBKB, InputHBKB);
						} else {
								sftd_draw_textf(font, 10, 50, RGBA8(0, 255, 0, 255), 10, "x: %d , y: %d", touch.px, touch.py);
						}
					} else {
						sftd_draw_textf(font, 130, 120, RGBA8(0, 255, 0, 255), 10, "Press A to start!");
					}
				}  
				gameStatus[7] = ~gameStatus[7];
			};
		
		void keyboardCalling(HB_Keyboard &sHBKB, std::string &InputHBKB) {
			u8 KBState = sHBKB.HBKB_CallKeyboard(touch);
			InputHBKB = sHBKB.HBKB_CheckKeyboardInput();
			if(KBState == 1) { // Enter Key
				if(InputHBKB.size() <= 0 || InputHBKB.size() >= 20) {
					InputHBKB = "Yung PAULy D";
				}
				
				gameStatus[6] = ~gameStatus[6];
			} else if(KBState == 3) { // Cancel Key
				sHBKB.HBKB_Clean();
				InputHBKB = "";
			}
		};
			/*
			void pickSaveFile() {
				
			}
			
			void createSaveFile() {
				
			}
			
			void loadSaveFile() {
				
			}
			*/
};
