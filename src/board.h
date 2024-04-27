#ifndef _BOARD_H
#define _BOARD_H

#define DEBUG_BOARD  1

#define width  12
#define height 22
int board[width][height];

void init_board() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height-1 || j == 0 || j == width-1) {
                board[j][i] = 7;
            } else {
                board[j][i] = 0;
            }
        }
    }
}

void clear_board() {
    for (int i = 1; i <  height-1; i++) {
        for (int j = 1; j < width-1; j++) {
            if (board[j][i] == 1) {
                board[j][i] = 0;
            }
        }
    }
}

void draw_board() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (board[j][i])
            {
                case 1:
                    printw("O");
                    break;
                case 2:
                    printw("0");
                    break;
                case 7:
                    printw("#");
                    break;
                case 8:
                    printw("=");
                    break;
                default:
                    printw(" ");
                    break;
            }
        }

        if (DEBUG_BOARD) {
            printw("  ");
            for (int j = 0; j < width; j++) {
                printw("%d", board[j][i]);
            }
        }
        printw("\n");
    }
    clear_board();
}

int check_lines() {
    int line = 0;
    for (int i = 1; i <  height-1; i++) {
        line = 0;
        for (int j = 1; j < width-1; j++) {
            if (board[j][i] == 2) {
                line++;
            }
        }
        if (line == width-2) {
            return i;
        }
    }
    return -1;
}

void delete_line(int line) {
    for (int i = line; i > 1; i--) {
        for (int j = 1; j < width-1; j++) {
            if (board[j][i] != 7) {
                board[j][i] = board[j][i-1];
            }
        }
    }
}

#endif  /* board.h guard */