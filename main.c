#include "life.h"
//
// 	LIFE.gb Driver Code
//	Original Algortihm by:			John H. Conway
//	Written for the GameBoy by:		Miguel Ramos
//
//	Version:						12-19-25
//
//	Description:					Handles user input for controlling the Game of LIFE
//
//

uint8_t joy_held;
uint8_t joy_pressed;
uint8_t joy_released;

void input_update(void);

void main(void)
{
	DISPLAY_ON;
	SHOW_BKG;

	set_bkg_data(0, 28, life_tile_label);
	// Main driver loop
	while (1)
	{
		// Load title splash onto screen
		set_bkg_tiles(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, life_bkg);
		// Seed random initial board state from user input
		delay(100);
		int seeded = 0;
		while (!seeded)
		{
			input_update();

			if(joy_pressed)
			{
				init_board_rand(joy_pressed + sys_time);
				seeded = 1;
			}

			wait_vbl_done();
		}
		// Clear Screen
		for (uint8_t y = 0; y < SCREEN_HEIGHT; y++)
		{
			for (uint8_t x = 0; x < SCREEN_WIDTH; x++)
			{
				set_bkg_tile_xy(x, y, DEAD_INDEX);
			}
		}
		// Game of Life Loop
		uint8_t running = 1;
		while (running)
		{
			input_update();

			if (joy_pressed & J_START)
			{
				break;
			}
			update_board();
			draw_life_board();

			wait_vbl_done();
		}
	}
}


void input_update(void)
{
	static uint8_t prev;

	joy_held = joypad();
	joy_pressed = (joy_held) & (~prev);
	joy_released = (~joy_held) & (prev);

	prev = joy_held;
}