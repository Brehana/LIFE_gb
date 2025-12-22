#include<gb/gb.h>
#include<rand.h>  
#include<stdio.h> 
#include"life_tile_set.h"
#include"life_bkg.h"

/*
*   LIFE.gb "life" header
*	Original Algortihm by:			John H. Conway
*	Written for the GameBoy by:		Miguel Ramos
*
*	Version:						12-22-25
*   
*   Description:					Header file for life.c
*
*/

#define SCREEN_HEIGHT 18
#define SCREEN_WIDTH 20

#define DEAD_INDEX 0
#define ALIVE_INDEX 1

void update_board(void);
uint8_t will_cell_live(uint8_t, uint8_t, uint8_t[][]);
void draw_life_board(void);
void init_board_rand(uint16_t);