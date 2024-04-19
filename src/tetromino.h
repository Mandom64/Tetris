#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdlib.h>
#include "board.h"
#include "common.h"

#define TMINOS 5
#define BLOCKS 4

typedef struct {
    Vec2 block[BLOCKS];
} Tetromino;
Tetromino *orig = NULL;
Tetromino *curr_piece = NULL;

void init_tminos() {
    curr_piece = malloc(sizeof(Tetromino));
    orig = malloc(TMINOS * sizeof(Tetromino));
    // oooo
    orig[0].block[0] = (Vec2){(WIDTH / 2 - 2) + 1, 1}; 
    orig[0].block[1] = (Vec2){(WIDTH / 2 - 2) + 1, 2};
    orig[0].block[2] = (Vec2){(WIDTH / 2 - 2) + 1, 3};
    orig[0].block[3] = (Vec2){(WIDTH / 2 - 2) + 1, 4};
    // oo
    //  oo
    orig[1].block[0] = (Vec2){(WIDTH / 2 - 2) + 1, 1};
    orig[1].block[1] = (Vec2){(WIDTH / 2 - 2) + 1, 2};
    orig[1].block[2] = (Vec2){(WIDTH / 2 - 2) + 2, 2};
    orig[1].block[3] = (Vec2){(WIDTH / 2 - 2) + 2, 3};
    // oo
    // oo
    orig[2].block[0] = (Vec2){(WIDTH / 2 - 2) + 1, 1};
    orig[2].block[1] = (Vec2){(WIDTH / 2 - 2) + 2, 1};
    orig[2].block[2] = (Vec2){(WIDTH / 2 - 2) + 1, 2};
    orig[2].block[3] = (Vec2){(WIDTH / 2 - 2) + 2, 2};
    // ooo
    //   o
    orig[3].block[0] = (Vec2){(WIDTH / 2 - 2) + 1, 1};
    orig[3].block[1] = (Vec2){(WIDTH / 2 - 2) + 1, 2};
    orig[3].block[2] = (Vec2){(WIDTH / 2 - 2) + 1, 3};
    orig[3].block[3] = (Vec2){(WIDTH / 2 - 2) + 2, 3};
    // ooo
    //  o 
    orig[4].block[0] = (Vec2){(WIDTH / 2 - 2) + 1, 1};
    orig[4].block[1] = (Vec2){(WIDTH / 2 - 2) + 1, 2};
    orig[4].block[2] = (Vec2){(WIDTH / 2 - 2) + 1, 3};
    orig[4].block[3] = (Vec2){(WIDTH / 2 - 2) + 2, 2};
}

void draw_piece(Tetromino *tmino) {
    for(int j = 0; j < BLOCKS; j++) {
        board[tmino->block[j].x][tmino->block[j].y] = 1;
    }
}

bool collision(Tetromino *tmino) {
    for(int k = 0; k < BLOCKS; k++) {
        if(tmino->block[k].y == HEIGHT-2) {
            return true;
        }
        if(board[tmino->block[k].x][tmino->block[k].y+1] == 2) {
            return true;
        }
    }

    return false;
}

void copy_tmino(Tetromino *t1, Tetromino *t2) {
    for(int i = 0; i < BLOCKS; i++) {
        t1->block[i] = t2->block[i];
    }
}

void move_tmino(Tetromino *tmino, int deltaX, int deltaY) {
    // Border check
    for(int i = 0; i < BLOCKS; i++) {
        if((tmino->block[i].x+deltaX) == 0 || 
           (tmino->block[i].y+deltaY) == 0 || 
           (tmino->block[i].x+deltaX) == WIDTH-1 || 
           (tmino->block[i].y+deltaY) == HEIGHT-1) {
                return;
           }
    }

    for(int i = BLOCKS; i >= 0; i--) {
        tmino->block[i].x += deltaX;
        tmino->block[i].y += deltaY;
    }
}

void rest_tmino(Tetromino *t) {
    for(int i = 0; i < BLOCKS; i++) {
        board[t->block[i].x][t->block[i].y] = 2;
    }
}

void rotate_tmino(Tetromino *t) {

}

int rand_tmino() {
    return n_rand(0, 3);
}

#endif // TETROMINO_H GUARD