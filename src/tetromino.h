#ifndef _TETROMINO_H
#define _TETROMINO_H

#define BLOCKS 4
typedef struct Tmino {
    Point block[BLOCKS];
} Tmino;

Tmino orig_piece[5];
Tmino curr_piece;

void copy_tmino(Tmino *t1, Tmino *t2) {
    for (int i = 0; i < BLOCKS; i++) {
        t1->block[i].x = t2->block[i].x;
        t1->block[i].y = t2->block[i].y;
    }
}

void rotate_tmino(Tmino *t) {
    int x, y;
    Point p = t->block[1];

    for (int i = 0; i < BLOCKS; i++) {
        x = t->block[i].y - p.y;
        y = t->block[i].x - p.x;
        t->block[i].x = p.x - x;
        t->block[i].y = p.y + y;
    }
}

int rand_tmino() { return n_rand(0, 3);}

void init_tminos() {
    // oooo
    orig_piece[0].block[0] = (Point){(width / 2 - 2) + 1, 1}; 
    orig_piece[0].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_piece[0].block[2] = (Point){(width / 2 - 2) + 1, 3};
    orig_piece[0].block[3] = (Point){(width / 2 - 2) + 1, 4};
    // oo
    //  oo
    orig_piece[1].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_piece[1].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_piece[1].block[2] = (Point){(width / 2 - 2) + 2, 2};
    orig_piece[1].block[3] = (Point){(width / 2 - 2) + 2, 3};
    // oo
    // oo
    orig_piece[2].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_piece[2].block[1] = (Point){(width / 2 - 2) + 2, 1};
    orig_piece[2].block[2] = (Point){(width / 2 - 2) + 1, 2};
    orig_piece[2].block[3] = (Point){(width / 2 - 2) + 2, 2};
    // ooo
    //   o
    orig_piece[3].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_piece[3].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_piece[3].block[2] = (Point){(width / 2 - 2) + 1, 3};
    orig_piece[3].block[3] = (Point){(width / 2 - 2) + 2, 3};
    // ooo
    //  o 
    orig_piece[4].block[0] = (Point){(width / 2 - 2) + 1, 1};
    orig_piece[4].block[1] = (Point){(width / 2 - 2) + 1, 2};
    orig_piece[4].block[2] = (Point){(width / 2 - 2) + 1, 3};
    orig_piece[4].block[3] = (Point){(width / 2 - 2) + 2, 2};

    copy_tmino(&curr_piece, &orig_piece[0]);
}

void draw_piece(Tmino t) {
    int x, y;

    for (int j = 0; j < BLOCKS; j++) {
        x = t.block[j].x;
        y = t.block[j].y; 
        board[x][y] = 1;
    }
}

void lock_tmino(Tmino *t) {
    int x, y;

    for (int i = 0; i < BLOCKS; i++) {
        x = t->block[i].x;
        y = t->block[i].y;
        board[x][y] = 2;
    }
}

bool can_fit(Tmino *t, int deltaX, int deltaY) {
    int x, y;
    Tmino new_t;
    copy_tmino(&new_t, t);

    for (int i = BLOCKS-1; i >= 0; i--) {
        new_t.block[i].x += deltaX;
        new_t.block[i].y += deltaY;
    }
    
    for (int i = 0; i < BLOCKS; i++) {
        x = new_t.block[i].x;
        y = new_t.block[i].y;
        if (board[x][y] != 0) {
            return false;
        }
    }

    return true;
}

void move_tmino(Tmino *curr_piece, int deltaX, int deltaY) {
    int x, y;
    bool floor_reached = false;

    /* Collision checks */
    for (int i = 0; i < BLOCKS; i++) {
        x = curr_piece->block[i].x + deltaX;
        y = curr_piece->block[i].y + deltaY;

        if (x < 0 || x >= width-1 || y < 0 || y >= height-1) {
            return; /* Border collision, can't move further */
        }

        if (curr_piece->block[i].y == height-2) {
            floor_reached = true; /* Bottom collision, can't move further */
        }
    }

    /* Does piece fits? if yes move else spawn new one */
    if ((!can_fit(curr_piece, 0, 1)) || floor_reached) {
        lock_tmino(curr_piece);
        copy_tmino(curr_piece, &orig_piece[rand_tmino()]);
    } else if (can_fit(curr_piece, deltaX, deltaY)) {
        for (int i = BLOCKS-1; i >= 0; i--) {
            curr_piece->block[i].x += deltaX;
            curr_piece->block[i].y += deltaY;
        }
    } 
}

#endif  /* tetromino.h guard */