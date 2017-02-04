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

namespace cxsimulator {
	void render(touchPosition &touch, std::bitset<8> &gameStatus, std::string &InputHBKB, u32 &kDown, HB_Keyboard &sHBKB, sftd_font *font);
	void keyboardCalling(HB_Keyboard &sHBKB, std::string &InputHBKB);
};