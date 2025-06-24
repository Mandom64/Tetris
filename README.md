# Ascii Tetris

Written in C99 using ncurses.h

## Controls

- **Up Arrow:** Rotate current tetromino
- **Left/Right Arrow:** Move tetromino

# Build and run(on linux)
```
./build.sh compile
./build.sh run
```

# Or compile manually 
```
gcc -Wall -Wextra src/main.c -o build/tetris -lncurses
```