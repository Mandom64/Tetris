#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <ncurses/ncurses.h>
#include "common.h"
#include "board.h"
#include "tetromino.h"

#define TICK_RATE 100
bool quit = false;

void handle_input(Tmino *curr_piece) {
    switch(getch()) {
        case 27:
            quit = true;
            break;
        case KEY_UP:
            rotate_tmino(curr_piece);
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

void game_tick() {
    move_tmino(&curr_piece, 0, 1);
    Sleep(TICK_RATE);
}

int main() {
    /* Set random seed */
    srand(time(NULL));

    /* Ncurses stuff */
    initscr();
    cbreak();
    noecho(); 
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    /* Initialize stuff */
    init_board();
    init_tminos();

    int ticks = 0;
    int line = -1;
    
    /* Main game loop */
    while(!quit) {
            clear();

            /* First draw the falling piece, then the board */
            draw_piece(curr_piece);
            draw_board();
            /* Text goes under the board */
            printw("Ticks:%d\n", ticks++);
            handle_input(&curr_piece);
            game_tick();

            /* Check for full lines, if there are any delete */
            while((line = check_lines()) != -1) {
                clear();
                for (int i = 1; i < width-1; i++) {
                    board[i][line] = 8;
                }
                /* This is a small animation for deleting the line */
                draw_board();
                refresh();
                Sleep(500);
                delete_line(line);
            }

            refresh();
    }

    /* Cleanup */
    endwin();

    return 0;
}