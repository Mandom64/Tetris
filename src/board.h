#ifndef BOARD_H
#define BOARD_H

#include <stdio.h>
#include <ncurses/ncurses.h>
#define DEBUG  1

#define WIDTH  12
#define HEIGHT 22
int board[WIDTH][HEIGHT];

void init_board() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(i == 0 || i == HEIGHT-1 || j == 0 || j == WIDTH-1) {
                board[j][i] = 7;
            } else {
                board[j][i] = 0;
            }
        }
    }
}

void draw_board() {
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            if(board[j][i] == 1) {
                printw("O");
            }
            else if(board[j][i] == 2) {
                printw("O");
            } else if(board[j][i] == 7) {
                printw("#");
            } else {
                printw(" ");
            }
        }
        if(DEBUG) {
            printw("  ");
            for(int j = 0; j < WIDTH; j++) {
                printw("%d", board[j][i]);
            }
        }
        printw("\n");
    }
}

void clear_board() {
    for(int i = 1; i <  HEIGHT-1; i++) {
        for(int j = 1; j < WIDTH-1; j++) {
            if(board[j][i] == 1) {
                board[j][i] = 0;
            }
        }
    }
}

int check_lines() {
    for(int i = 1; i <  HEIGHT-1; i++) {
        int line = 0;
        for(int j = 1; j < WIDTH-1; j++) {
            if(board[j][i] == 2) {
                line++;
            }
        }
        if(line == WIDTH-2) {
            return i;
        }
    }
    return -1;
}

void delete_line(int line) {
    for(int i = line; i < HEIGHT-1; i++) {
        for(int j = 1; j < WIDTH-1; j++) {
            board[j][i] = board[j][i+1];
        }
    }
}

#endif // BOARD_H GUARD