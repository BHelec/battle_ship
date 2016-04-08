#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <termios.h>

enum _phase {
    load = 0,
    begin_chose_pos,
    choose_posA,
    choose_posB,
    begin_attack,
    Aattack,        //5
    Aview,
    Battack,
    Bview,
    win,
    quit_game,      //10
};

//ui.c
char get_key ();
void print_block_blink (int abs_pos);
void print_grid ();
void print_hints ();
void print_status ();
void update_display (enum _phase phase);

//library.c

