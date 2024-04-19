#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
#include <ncurses/ncurses.h>
#include "board.h"
#include "common.h"
#include "tetromino.h"

#define TICK_RATE 75

void get_input(Tetromino *curr_piece) {
    switch(getch()) {
        case KEY_UP:
            //rotate_tmino(curr_piece, 90);
            break;
        case KEY_DOWN:
            move_tmino(curr_piece, 0, 1);
            move_tmino(curr_piece, 0, 1);
            break;
        case KEY_LEFT:
            move_tmino(curr_piece, -1, 0);
            break;
        case KEY_RIGHT:
            move_tmino(curr_piece, 1, 0);
            break;
    }
}

void game_tick(Tetromino *curr_piece) {
    move_tmino(curr_piece, 0, 1);
    Sleep(TICK_RATE);
}

int main(int argc, char **argv) {
    // Set random seed
    srand(time(NULL));

    // Ncurses stuff
    initscr();
    cbreak();
    noecho(); 
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    // Initialize stuff
    init_board();
    init_tminos();
    copy_tmino(curr_piece, &orig[0]);

    int ticks = 0;
    int line_found = 0;
    while(1) {
        clear();
        draw_piece(curr_piece);
        draw_board();
        // Debug stuff
        printw("%d\n(%d, %d)\nline found:%d", ticks++, 
            curr_piece->block[0].x, curr_piece->block[0].y, check_lines());
        get_input(curr_piece);
        game_tick(curr_piece);
        // If collision rest the curr tmino and spawn a new one
        if(collision(curr_piece)) {
            rest_tmino(curr_piece);
            copy_tmino(curr_piece, &orig[rand_tmino()]);
        }
        // Check for full lines
        if((line_found = check_lines()) != -1) {
            delete_line(line_found);
            //Sleep(5000);
        }
        clear_board();
        refresh();
    }
    
    // Cleanup
    endwin();

    return 0;
}