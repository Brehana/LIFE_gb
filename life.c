#include "life.h"

/*
 *   LIFE.gb "life" Code
 *	Original Algortihm by:			John H. Conway
 *	Written for the GameBoy by:		Miguel Ramos
 *
 *	Version:						12-19-25
 *
 *   Description:					Implementation of the Game of Life cellular automata designed by
 *                                   J. Conway. Written and optimized to run on the Gameboy hardware.
 *
 */

//Storage buffers for computing board state.
uint8_t primary_board_buffer[SCREEN_WIDTH + 2][SCREEN_HEIGHT + 2];
uint8_t secondary_board_buffer[SCREEN_WIDTH + 2][SCREEN_HEIGHT + 2];

//Pointers for accessing board state.
uint8_t (*current_generation)[SCREEN_HEIGHT + 2] = primary_board_buffer;
uint8_t (*next_generation)[SCREEN_HEIGHT + 2]    = secondary_board_buffer;

// Initializes board to random state using seed.
void init_board_rand(uint16_t seed)
{
    initrand(seed);
    for (uint8_t x = 1; x <= SCREEN_WIDTH; x++)
    {
        for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++)
        {
            current_generation[x][y] = rand() % 2;
        }
    }
}

// Draws board stored in life_board[][] to screen.
void draw_life_board(void)
{
    for (uint8_t x = 1; x <= SCREEN_WIDTH; x++)
    {
        for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++)
        {
            set_bkg_tile_xy(x - 1, y - 1, current_generation[x][y] ? ALIVE_INDEX : DEAD_INDEX);
        }
    }
}

// Computes state of next_generation generation based on state of current_generation generation, then
// stores next_generation generation in life_board.
void update_board(void)
{

    //I. Pad edges to enable edge wrapping
    for (uint8_t x = 1; x <= SCREEN_WIDTH; x++)
    {
        current_generation[x][0] = current_generation[x][SCREEN_HEIGHT];
        current_generation[x][SCREEN_HEIGHT + 1] = current_generation[x][1];
    }

    for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++)
    {
        current_generation[0][y] = current_generation[SCREEN_WIDTH][y];
        current_generation[SCREEN_WIDTH + 1][y] = current_generation[1][y];
    }

    // II. For Each Cell...
    for (uint8_t x = 1; x <= SCREEN_WIDTH; x++) {
        for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++) {

            uint8_t neighbors =
                current_generation[x-1][y-1] + current_generation[x][y-1] + current_generation[x+1][y-1] +
                current_generation[x-1][y]   +                  current_generation[x+1][y]   +
                current_generation[x-1][y+1] + current_generation[x][y+1] + current_generation[x+1][y+1];

            uint8_t alive = current_generation[x][y];

            next_generation[x][y] =
                (alive && (neighbors == 2 || neighbors == 3)) ||
                (!alive && neighbors == 3);
        }
    }

    // V. Swap current_generation/next_generation boards
    uint8_t (*tmp)[SCREEN_HEIGHT + 2] = current_generation;
    current_generation = next_generation;
    next_generation = tmp;
}