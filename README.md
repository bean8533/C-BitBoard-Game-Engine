# CS 3503 Project 1 - BitBoard Checkers Game

## Author
Benjamin Lam

## Build Instructions
```bash
gcc -o checkers main.c bitboard.c checkers.c
```

## Gameplay Instructions
### Objective
- Capture all opponent pieces by jumping over them onto an empty square
- Reaching the opponent's last row changes your piece to a king, which allows forward and backward movement

### Layout 
Squares are numbered from 0 to 63, the numbers shown below are legal squares
```
------------------------------
| 56  -  58  -  60  -  62  - |
| -  49  -  51  -  53  -  55 |
| 40  -  42  -  44  -  46  - |
| -  33  -  35  -  37  -  39 |
| 24  -  26  -  28  -  30  - |
| -  17  -  19  -  21  -  23 |
| 8   -  10  -  12  -  14  - |
| -  1   -  3   -  5   -  7  |
------------------------------
```