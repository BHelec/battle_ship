#include "battle_ship.h"
#include <stdbool.h>

char get_key () {
    char signal;
    char key;
    bool escape;
    signal = getchar ();
    if (0x1b == signal) {
        escape = true;
        if (0x5b == getchar ()) {
            signal = getchar ();
        }
    } else {
        escape = false;
    }

    if (escape) {
        switch (signal) {
            case 0x41:
                key = 'U';
                break;
            case 0x42:
                key = 'D';
                break;
            case 0x43:
                key = 'R';
                break;
            case 0x44:
                key = 'L';
                break;
            default:
                key = 'x';
                break;
        }
    } else {
        switch (signal) {
            case 0x77: case 0x57:
                key = 'U';
                break;
            case 0x73: case 0x53:
                key = 'D';
                break;
            case 0x64: case 0x44:
                key = 'R';
                break;
            case 0x61: case 0x41:
                key = 'L';
                break;
            case 0x72: case 0x52:
                key = 'r';
                break;
            case 0x71: case 0x51:
                key = 'q';
                break;
            case 0x69: case 0x49: case 0x68: case 0x48:
                key = 'h';
                break;
            default:
                key = 'x';
                break;
        }
    }
    return key;
}
