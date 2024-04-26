#ifndef _TETROMINO_H
#define _TETROMINO_H

#include <stdlib.h>
#include "board.h"
#include "common.h"

#define BLOCKS 4

typedef struct {
    Point block[BLOCKS];
} Tmino;
Tmino *orig_pieces;
Tmino *curr_piece;

Tmino *create_tminos(int size) {
    Tmino *tminos = malloc(size * sizeof(Tmino));
    return tminos;
}

void copy_tmino(Tmino *t1, Tmino *t2) {
    for(int i = 0; i < BLOCKS; i++) {
        t1->block[i] = t2->block[i];
    }
}

void init_tminos() {
    orig_pieces = create_tminos(5);
    // oooo
    orig_pieces[0].block[0] = (Point){(width / 2 - 2) + 1, 1}; 
    orig_pieces[0].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_pieces[0].block[2] = (Point){(width / 2 - 2) + 1, 3};
    orig_pieces[0].block[3] = (Point){(width / 2 - 2) + 1, 4};
    // oo
    //  oo
    orig_pieces[1].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_pieces[1].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_pieces[1].block[2] = (Point){(width / 2 - 2) + 2, 2};
    orig_pieces[1].block[3] = (Point){(width / 2 - 2) + 2, 3};
    // oo
    // oo
    orig_pieces[2].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_pieces[2].block[1] = (Point){(width / 2 - 2) + 2, 1};
    orig_pieces[2].block[2] = (Point){(width / 2 - 2) + 1, 2};
    orig_pieces[2].block[3] = (Point){(width / 2 - 2) + 2, 2};
    // ooo
    //   o
    orig_pieces[3].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_pieces[3].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_pieces[3].block[2] = (Point){(width / 2 - 2) + 1, 3};
    orig_pieces[3].block[3] = (Point){(width / 2 - 2) + 2, 3};
    // ooo
    //  o 
    orig_pieces[4].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_pieces[4].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_pieces[4].block[2] = (Point){(width / 2 - 2) + 1, 3};
    orig_pieces[4].block[3] = (Point){(width / 2 - 2) + 2, 2};

    curr_piece = create_tminos(1);
    copy_tmino(curr_piece, &orig_pieces[0]);
}

void draw_curr_piece(Tmino *t) {
    for(int j = 0; j < BLOCKS; j++) {
        int x = t->block[j].x;
        int y = t->block[j].y; 

        board[x][y] = 1;
    }
}

int rand_tmino() {
    return n_rand(0, 3);
}

bool piece_collision(Tmino *t) {
    for(int i = 0; i < BLOCKS; i++) {
        int x = t->block[i].x;
        int y = t->block[i].y;

        if(board[x][y] == 2) {
            return true;
        }
    }
    return false;
}

bool bottom_collision(Tmino *t) {
    for(int i = 0; i < BLOCKS; i++) {
        if(t->block[i].y == height-2) {
            return true;
        }
    }
    return false;
}

bool can_fit(Tmino *t, int deltaX, int deltaY) {
    Tmino *next_move = malloc(sizeof(Tmino));
    copy_tmino(next_move, t);

    for(int i = BLOCKS-1; i >= 0; i--) {
        next_move->block[i].x += deltaX;
        next_move->block[i].y += deltaY;
    }
    
    for(int i = 0; i < BLOCKS; i++) {
        int x = next_move->block[i].x;
        int y = next_move->block[i].y;

        if(board[x][y] != 0) {
            return false;
        }
    }
    free(next_move);
    return true;
}

void lock_tmino(Tmino *t) {
    for(int i = 0; i < BLOCKS; i++) {
        int x = t->block[i].x;
        int y = t->block[i].y;

        board[x][y] = 2;
    }
}

void spawn_tmino() {
    lock_tmino(curr_piece);
    copy_tmino(curr_piece, &orig_pieces[rand_tmino()]);
}

void move_tmino(Tmino *curr_piece, int deltaX, int deltaY) {
    // Border check
    for(int i = 0; i < BLOCKS; i++) {
        int x = curr_piece->block[i].x + deltaX;
        int y = curr_piece->block[i].y + deltaY;

        if (x < 0 || x >= width-1 || y < 0 || y >= height-1) {
            return;
        }
    }

    // Does piece fits? if yes move else spawn new one
    if((!can_fit(curr_piece, 0, 1)) || bottom_collision(curr_piece)) {
        spawn_tmino(curr_piece);
    } else if(can_fit(curr_piece, deltaX, deltaY)) {
        for(int i = BLOCKS-1; i >= 0; i--) {
            curr_piece->block[i].x += deltaX;
            curr_piece->block[i].y += deltaY;
        }
    } 
}

// Rotation found from here "https://www.youtube.com/watch?v=zH_omFPqMO4&t=186s"
void rotate_tmino(Tmino *t) {
    // TODO: implement this
    Point p = t->block[1];
    for(int i = 0; i < BLOCKS; i++) {
        int x = t->block[i].y - p.y;
        int y = t->block[i].x - p.x;
        t->block[i].x = p.x - x;
        t->block[i].y = p.y + y;
    }
}


#endif /* tetromino.h guard */