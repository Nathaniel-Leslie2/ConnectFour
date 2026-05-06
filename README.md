# Connect Four (C, Terminal)

A fully playable **two-player Connect Four** game written in C for the terminal.

## Features

- Classic 7-column by 6-row Connect Four board.
- Two local players taking alternating turns (`X` and `O`).
- Input validation for out-of-range columns and malformed values.
- Win detection for all four directions:
  - Horizontal
  - Vertical
  - Diagonal (down-right)
  - Diagonal (down-left)
- Draw detection when the board is full.
- Optional quit command (`q` or `Q`) at any prompt.

## Project Structure

- `main.c` — Core game logic (board state, input handling, move placement, win/draw checks, game loop).
- `Makefile` — Build and clean targets.
- `README.md` — Project documentation.

## Requirements

- A C compiler that supports C11 (e.g., `gcc` or `clang`)
- `make`

## Build

```bash
make
```

This produces an executable named `connect_four`.

## Run

```bash
./connect_four
```

## Controls

- Enter a number from `1` to `7` to drop a piece into that column.
- Enter `q` (or `Q`) to quit.

## Example Session

```text
Connect Four (Terminal Edition)
Players take turns dropping pieces into columns 1-7.
Type q to quit.

| . . . . . . . |
| . . . . . . . |
| . . . . . . . |
| . . . . . . . |
| . . . . . . . |
| . . . . . . . |
  1 2 3 4 5 6 7

Player X, choose a column (1-7) or q to quit:
```

## Development Notes

- The board uses `.` for empty cells, `X` for player one, and `O` for player two.
- A move is inserted from the bottom of a column upward, matching real Connect Four rules.
- Win checks are evaluated after each move using directional scanning around the latest piece.

## Testing

Basic validation performed:

- Successful compilation with warning flags enabled.
- Automated non-interactive run using piped input to confirm game flow and victory detection.

Commands used:

```bash
make
printf '1\n1\n2\n2\n3\n3\n4\n' | ./connect_four
make clean
```

## Future Improvements

- Single-player mode with a basic AI.
- Better terminal UI (colors, cursor movement, and board redraw optimizations).
- Save/load game state.
- Unit tests for input parsing and win-condition logic.
