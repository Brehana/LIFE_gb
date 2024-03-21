#include"life.h"

#define SCREEN_HEIGHT 18
#define SCREEN_WIDTH 20

#define DEAD_INDEX 0
#define ALIVE_INDEX 1

/*
*   LIFE.gb "life" Code
*	Original Algortihm by:			John H. Conway
*	Written for the GameBoy by:		Miguel Ramos
*
*	Version:						03-21-24
*   
*   Description:					Implementation of the Game of Life cellular automata designed by 
*                                   J. Conway. Written and optimized to run on the Gameboy Original hardware.
*
*/

//Storage for current board state.
uint8_t life_board[SCREEN_WIDTH + 2][SCREEN_HEIGHT + 2];

//Initializes board to random state using seed.
void init_board_rand(uint16_t seed){
    initrand(seed);
    for (uint8_t x = 1; x <= SCREEN_WIDTH; x++){
        for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++) {
            life_board[x][y] = rand() % 2;
        }
    }
}
//Draws board stored in life_board[][] to screen.
void draw_life_board(void){                                            
    uint16_t start = sys_time;
     for (uint8_t x = 1; x <= SCREEN_WIDTH; x++){
        for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++) {
            if(life_board[x][y]){
                set_bkg_tile_xy(x-1, y-1, ALIVE_INDEX);
            }
            else{
                set_bkg_tile_xy(x-1, y-1, DEAD_INDEX);
            }
        }
    }
}
//Determines whether cell table[x][y] will live into next generation.
//Returns:      1 - cell table[x][y] lives.
//              0 - cell table[x][y] dies.
uint8_t will_cell_live(uint8_t x, uint8_t y, uint8_t table[SCREEN_WIDTH + 2][SCREEN_HEIGHT + 2]){
    uint16_t start = sys_time;
    uint8_t living_neighbors = 0;

    for(int8_t i = -1; i <= 1; i++){
        for(int8_t j = -1; j <= 1; j++){
                uint8_t index_x = (x + i);
                uint8_t index_y = (y + j);
                //Wrapping without modulus
                if(index_x == 0){
                    index_x = SCREEN_WIDTH;
                }
                if(index_x == SCREEN_WIDTH + 1){
                    index_x = 1;
                }
                if(index_y == 0){
                    index_y = SCREEN_HEIGHT;
                }
                if(index_y == SCREEN_HEIGHT + 1){
                    index_y = 1;
                }
                if(table[index_x][index_y] > 0){
                    living_neighbors++;
            }
        }
    }
    if(table[x][y]){        //  For unknown reasons, ignoring the current cell while
        living_neighbors--; //counting neighbors breaks everything. The only reliable way
    }                       //to make this function behave is to subtract the current cell
                            //from living_neighbors afterwards.
    if(table[x][y] > 0 && (living_neighbors == 2 || living_neighbors == 3)){
        return 1;
    }
    else if(table[x][y] == 0 && living_neighbors == 3){
        return 1;
    }
    else{
        return 0;
    }
}
//Computes state of next generation based on state of current generation, then
//stores next generation in life_board.
void update_board(void){
    uint16_t start = sys_time;
    uint8_t temp_new_board[SCREEN_WIDTH + 2][SCREEN_HEIGHT + 2];

    //I. For Each Cell...
    for (uint8_t x = 1; x <= SCREEN_WIDTH; x++){
        for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++) {
            //- Compute whether cell lives or dies
            uint8_t living = will_cell_live(x, y, life_board);
            //- Store in temporary table
            temp_new_board[x][y] = living;
        }
    }

    //II. Copy new board state back uint8_to life_board
    for (uint8_t x = 1; x <= SCREEN_WIDTH; x++){
        for (uint8_t y = 1; y <= SCREEN_HEIGHT; y++) {
            life_board[x][y] = temp_new_board[x][y];
        }
    }
}