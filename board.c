#include <stdio.h>
#include "board.h"

void board_init(Board *b) {
    for (int r = 0; r < C4_ROWS; ++r)
        for (int c = 0; c < C4_COLS; ++c)
            b->cells[r][c] = 0;
}

void board_print(const Board *b) {
    /* column headers */
    printf("\n");
    printf("  ");
    for (int c = 0; c < C4_COLS; ++c) {
        printf(" %d", c + 1);
    }
    printf("\n");

    for (int r = 0; r < C4_ROWS; ++r) {
        printf("| ");
        for (int c = 0; c < C4_COLS; ++c) {
            int v = b->cells[r][c];
            char ch = (v == 0) ? '.' : (v == 1 ? 'X' : 'O');
            printf("%c ", ch);
        }
        printf("|\n");
    }
    printf("\n");
}

int board_drop(Board *b, int col, int player) {
    if (col < 1 || col > C4_COLS) return -1;
    int c = col - 1;
    for (int r = C4_ROWS - 1; r >= 0; --r) {
        if (b->cells[r][c] == 0) {
            b->cells[r][c] = player;
            return r;
        }
    }
    return -1; /* column full */
}

int board_is_full(const Board *b) {
    for (int r = 0; r < C4_ROWS; ++r)
        for (int c = 0; c < C4_COLS; ++c)
            if (b->cells[r][c] == 0) return 0;
    return 1;
}

static int check_dir(const Board *b, int r, int c, int dr, int dc, int player) {
    int count = 0;
    for (int k = 0; k < 4; ++k) {
        int rr = r + k * dr;
        int cc = c + k * dc;
        if (rr < 0 || rr >= C4_ROWS || cc < 0 || cc >= C4_COLS) return 0;
        if (b->cells[rr][cc] != player) return 0;
        ++count;
    }
    return count == 4;
}

int board_check_win(const Board *b, int player) {
    for (int r = 0; r < C4_ROWS; ++r) {
        for (int c = 0; c < C4_COLS; ++c) {
            if (b->cells[r][c] != player) continue;
            /* check four directions: right, down, down-right, up-right */
            if (check_dir(b, r, c, 0, 1, player)) return 1;
            if (check_dir(b, r, c, 1, 0, player)) return 1;
            if (check_dir(b, r, c, 1, 1, player)) return 1;
            if (check_dir(b, r, c, -1, 1, player)) return 1;
        }
    }
    return 0;
}
