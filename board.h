#ifndef CONNECT4_BOARD_H
#define CONNECT4_BOARD_H

#define C4_ROWS 6
#define C4_COLS 7

typedef struct {
    int cells[C4_ROWS][C4_COLS]; /* 0 = empty, 1 = player1, 2 = player2 */
} Board;

/* initialize board to empty */
void board_init(Board *b);

/* print board to stdout */
void board_print(const Board *b);

/* drop a piece for `player` into `col` (1-based).
   Returns the row index (0-based) where the piece landed, or -1 on failure. */
int board_drop(Board *b, int col, int player);

/* return 1 if board is full, 0 otherwise */
int board_is_full(const Board *b);

/* return 1 if `player` has a connect-4 on the board, else 0 */
int board_check_win(const Board *b, int player);

#endif /* CONNECT4_BOARD_H */
