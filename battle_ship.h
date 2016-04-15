#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>

#define COLS 64
#define ROWS 38

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
    int pos[5][5][2];
    bool alive[5][5];
};

const char *name[5] = {"Aircraft Carrier", "Battleship", "Submarine", "Destroyer", "Patrol Boat"};

//ui.c
char get_key ();
int get_pos ();
void print_block_blink (int abs_pos);
void print_grid ();
void print_hints (enum _state state);
void print_status ();
void update_display (enum _state state);
struct termios set_non_canonical ();
void set_canonical (struct termios old);

//library.c
void set_ship_pos (struct _player *player, int ctr_pos);
void set_ship_hit (struct _player *player, int hit_pos);
void check_end (struct _player *player);
