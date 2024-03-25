#include"life.c"
#include"include/gb/gb.h"
/*
* 	LIFE.gb Driver Code
*	Original Algortihm by:			John H. Conway
*	Written for the GameBoy by:		Miguel Ramos
*
*	Version:						03-21-24
*
*	Description:					Handles user input for controlling the Game of LIFE
*
*/
void main(void){
    DISPLAY_ON;
    SHOW_BKG;

    set_bkg_data(0, 28, life_tile_label);
	//Main driver loop
	while(1){
		//Load title splash onto screen
		set_bkg_tiles(0,0, SCREEN_WIDTH, SCREEN_HEIGHT, life_bkg);
		//Seed random initial board state from user input
		delay(100);
		int seeded = 0;
		while(!seeded) {
			switch(joypad()) {
				case J_RIGHT :
					init_board_rand(J_RIGHT + sys_time);
					seeded = 1;
					break;
				case J_LEFT :
					init_board_rand(J_LEFT + sys_time);
					seeded = 1;
				case J_UP :
					init_board_rand(J_UP + sys_time);
					seeded = 1;
				case J_DOWN :
					init_board_rand(J_DOWN + sys_time);
					seeded = 1;
				case J_START :
					init_board_rand(J_START + sys_time);
					seeded = 1;
				case J_SELECT :
					init_board_rand(J_SELECT + sys_time);
					seeded = 1;
				case J_A : 
					init_board_rand(J_A + sys_time);
					seeded = 1;
				case J_B : 
					init_board_rand(J_B + sys_time);
					seeded = 1;			
				default :
					break;
			}
		}
		//Clear Screen
		for (uint8_t y = 0; y < SCREEN_HEIGHT; y++) {
			for (uint8_t x = 0; x < SCREEN_WIDTH; x++) {
				set_bkg_tile_xy(x, y, DEAD_INDEX);
			}
		}
		//Game of Life Loop
		uint8_t running = 1;
		while(running){
			uint8_t joydata = joypad();
			update_board();
			draw_life_board();
			if(joypad() & J_START){
				running = 0;
			}
		}
	}
}