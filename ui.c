#include "battle_ship.h"

int main () {
    printf ("\e[s");            //store cursor position
    printf ("\e[?1049h");       //store window in buffer
    printf ("\e[2J");           //clear screen
    struct termios saved_state = set_non_canonical ();

    print_grid ();
    while (getchar () != 'q');

    set_canonical (saved_state);//reset terminal
    printf ("\e[u\n");          //restore cursor position
    printf ("\e[?1049l");       //restore the terminal window
    return EXIT_SUCCESS;
}

// For howard
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
            case 0x41: key = 'U'; break;
            case 0x42: key = 'D'; break;
            case 0x43: key = 'R'; break;
            case 0x44: key = 'L'; break;
            default:   key = 'x'; break;
        }
    } else {
        switch (signal) {
            case 0x77: case 0x57: key = 'U'; break;
            case 0x73: case 0x53: key = 'D'; break;
            case 0x64: case 0x44: key = 'R'; break;
            case 0x61: case 0x41: key = 'L'; break;
            case 0x72: case 0x52: key = 'r'; break;
            case 0x71: case 0x51: key = 'q'; break;
            case 0x69: case 0x49:
            case 0x68: case 0x48: key = 'h'; break;
            default:              key = 'x'; break;
        }
    }
    return key;
}

void print_grid () {
    unsigned short int r, c;        // row and column
    char column_num = 'A';
    bool labeled = false;

    printf ("\e[2;10H");
    for (r=0;r<ROWS;r++) {
        if (r % 3 == 1) {           // grid_size + 1
            printf ("\e[%d;%dH", r + 2, 8);
            for (c=0;c<COLS;c++) {
                if (c % 5 == 2) {   // grid_size * 2 + 1
                    printf ("+");
                } else {
                    printf ("-");
                }
            }
        } else {
            printf ("\e[%d;%dH", r + 2, 8);
            for (c=0;c<COLS;c++) {
                if (r == 0) {
                    if (c % 5 == 4) {
                        printf ("%c", column_num);
                        column_num++;
                        labeled = true;
                    }
                }
                if (c % 5 == 2) {   // grid_size * 2 + 1
                    printf ("|");
                } else {
                    if (labeled) {
                        labeled = false;
                        continue;
                    }
                    printf (" ");
                }
            }
            if (r % 3 == 2) {
                printf ("\e[%d;%dH%02d", r + 2, 8, r / 3 + 1);
            }
        }
    }
}

struct termios set_non_canonical () {
    struct termios old_info;
    tcgetattr(0, &old_info);
    struct termios info = old_info;
    info.c_lflag &= ~(ICANON | ECHO);
    info.c_cc[VMIN] = 1;
    info.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &info);
    return old_info;
}

void set_canonical (struct termios old) {
    tcsetattr(0, TCSANOW, &old);
}
