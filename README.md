# Ascii Tetris

Written in C99 using ncurses.h

## Controls

- **Left/Right Arrow:** Move tetromino
- **Up Arrow** Rotate current tetromino
- **Down Arrow** Increase fall speed

# Build and run(on linux)
```
./build.sh compile
./build.sh run
```

# Manual Compilation 
```
gcc -Wall -Wextra src/main.c -o build/tetris -lncurses
```

# TODO
- *Improve game feel*
- *Implement game state and score*