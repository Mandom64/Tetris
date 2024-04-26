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
bool quit = false;

void handle_input(Tmino *curr_piece) {
    switch(getch()) {
        case 27:
            quit = true;
            break;
        case KEY_UP:
            // TODO: rotate_tmino(curr_tmino);
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

// Ticks limit game speed and moves the falling piece down
void game_tick(Tmino *curr_tmino) {
    //move_tmino(curr_tmino, 0, 1);
    Sleep(TICK_RATE);
}

int main() {
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

    int ticks = 0;
    int full_line = -1;
    double start, end;
    // Main game loop
    while(!quit) {
        clear();
        start = GetTickCount();
        // First draw the falling piece, then the board
        draw_curr_piece(curr_piece);
        draw_board();
        handle_input(curr_piece);
        // Debug stuff goes under the board 
        end = GetTickCount();
        printw("Ticks:%d Falling Piece:(%d, %d) Line found:%d ms:%.2f\n", ticks++, curr_piece->block[0].x, 
            curr_piece->block[0].y, check_lines(), end-start);
        
        game_tick(curr_piece);
        
        // Check for full lines, if there are any delete
        while((full_line = check_lines()) != -1) {
            clear();
            for(int i = 1; i < width-1; i++) {
                board[i][full_line] = 8;
            }
            // This is a small animation for deleting the line
            draw_board();
            refresh();
            Sleep(500);
            delete_line(full_line);
        }
        refresh();
    }

    // Cleanup
    endwin();
    return 0;
}