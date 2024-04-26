#ifndef _COMMON_H
#define _COMMON_H

typedef struct {
    int x;
    int y;
} Point;

int n_rand(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

#endif /* common.h guard */