# CMD Tetris

A classic Tetris game implementation for Windows Command Prompt written in C with multithreading support.

## Features

- Classic Tetris gameplay with all standard tetrominos
- Colorful terminal graphics using ANSI escape codes
- Smooth gameplay with multi-threaded controls
- Real-time scoring system
- High score tracking
- Next piece preview
- Increasing difficulty as you progress

## Requirements

- Windows OS
- GCC compiler (MinGW recommended)
- pthread library (included with MinGW)

## How to Build

```bash
gcc main.c FramePrinter.c GameControls.c -o main.exe -lpthread
```

## How to Run

Simply execute the compiled binary:

```bash
./main.exe
```

## Game Controls

- **Arrow Left (←)**: Move piece left
- **Arrow Right (→)**: Move piece right
- **Arrow Down (↓)**: Soft drop (faster falling)
- **Arrow Up (↑)**: Rotate piece
- **Enter**: Start game / Select menu option

## Project Structure

```
cmd-tetris/
├── main.c              # Main game loop and initialization
├── FramePrinter.c      # Display and rendering functions (includes menu)
├── FramePrinter.h      # Display function declarations
├── GameControls.c      # Game logic and controls
├── GameControls.h      # Game logic declarations
├── MenuScreen.c        # Standalone ASCII art title screen program
└── libwinpthread-1.dll # pthread library for Windows
```

## How It Works

The game uses multi-threading to handle:
- Automatic piece falling
- User input for movement and rotation
- Screen refreshing

The game board is represented as a 24x10x2 three-dimensional array with mutex locks to prevent race conditions between threads.

## Author

Created by Isaias

## License

This project is open source and available for educational purposes.
