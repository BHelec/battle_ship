#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>

#define COLS 63
#define ROWS 38
/* The width and height for the grid */

enum _state {
    load = 0,
    begin_chose_pos,
    choose_posA,
    choose_posB,
    begin_attack,
    Aview,          //5
    Aattack,
    Bview,
    Battack,
    win,
    quit_game       //10
};

struct _player {
    bool alive[5][5];
    int old_pos;
    int pos[5][5][2];
};
/*
 * bool alive[5][5] : The hit status of the five ships
 * int old_column   : Last attack position column
 * int old_row      : Last attack position row
 * int pos[5][5][2] : Coordinate of the five ships, determined in state choose_pos
 */

typedef short int pos;
/*
 * Not used, only for description.
 * The position used by attacks and placement.
 * Using 1 for start and 12 for end.
 * Can have two variants:
 * 1. 0905: row first and then column, easy for debugging.
 * 2. 133 : (row - 1) * 12 + col, shorter, but harder to understand.
 */

const char *name[5] = {"Aircraft Carrier", "Battleship", "Submarine", "Destroyer", "Patrol Boat"};
/* The five ship names. Used for hints */

//ui.c
char get_key ();
/*
 * Get the key pressed from the user.
 * Part of the User Interface.
 * @return a char for labeling the key
 */ 

void map_key (char key);
/*
 * Identify the key pressed and do further operations.
 * Part of the User Interface.
 * @param the key char from get_key ()
 */

int get_pos ();         /* should be imbedded in `get_key ()` */
/*
 * Get the coordinates from the user of the attack or ship placement.
 * should be imbedded to: when the user press arrow keys, adjust the 
 * int values in the _player structure
 */

void print_block_blink (int abs_pos);
void print_grid (int start_pos);
void print_hints (enum _state state);
void print_status ();
void update_display (enum _state state);
struct termios set_non_canonical ();
void set_canonical (struct termios old);

//library.c
void set_ship_pos (struct _player *player, int ctr_pos);
void set_ship_hit (struct _player *player, int hit_pos);
void check_end (struct _player *player);
