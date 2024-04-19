#ifndef COMMON_H
#define COMMON_H

typedef struct {
    int x;
    int y;
} Vec2;

inline Vec2 vec2_add(Vec2 v1, Vec2 v2) {
    return (Vec2){v1.x + v2.x, v1.y + v2.y};
}

int n_rand(int min, int max) {
    return rand() % (max + 1 - min) + min;
}

#endif // COMMON_H GUARD