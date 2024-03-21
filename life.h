#include"include/gb/gb.h"
#include"include/rand.h"   
#include"life_tile_set.c"
#include"life_bkg.c"
#include<stdio.h>
/*
*   LIFE.gb "life" header
*	Original Algortihm by:			John H. Conway
*	Written for the GameBoy by:		Miguel Ramos
*
*	Version:						03-21-24
*   
*   Description:					Header file for life.c
*
*/

void update_board(void);
uint8_t will_cell_live(uint8_t, uint8_t, uint8_t[][]);
void draw_life_board(void);
void init_board_rand(uint16_t);