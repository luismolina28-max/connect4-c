#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

/* Helper: read an integer in range [min..max] from stdin with prompt. */
static int get_int_in_range(const char *prompt, int min, int max) {
    int val;
    int rc;
    while (1) {
        printf("%s", prompt);
        rc = scanf("%d", &val);
        if (rc != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        if (val < min || val > max) {
            printf("Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        return val;
    }
}

void game_run(void) {
    Board board;
    board_init(&board);
    printf("Choose game mode:\n");
    printf("1. Player vs Player\n");
    printf("2. Player vs Computer\n");
    int mode = get_int_in_range("Enter mode (1-2): ", 1, 2);

    srand((unsigned)time(NULL));

    int current = 1; /* player 1 starts */
    board_print(&board);

    while (1) {
        if (mode == 2 && current == 2) {
            /* simple computer move: pick a random valid column */
            int col, res;
            do {
                col = (rand() % C4_COLS) + 1;
                res = board_drop(&board, col, current);
            } while (res == -1);
            printf("Computer dropped a piece in column %d.\n", col);
        } else {
            char prompt[64];
            snprintf(prompt, sizeof(prompt), "Player %d - Select Column (1-%d): ", current, C4_COLS);
            int col = get_int_in_range(prompt, 1, C4_COLS);
            int res = board_drop(&board, col, current);
            if (res == -1) {
                printf("Column %d is full or invalid. Try again.\n", col);
                continue; /* same player tries again */
            }
        }

        board_print(&board);

        if (board_check_win(&board, current)) {
            if (mode == 2 && current == 2)
                printf("Computer wins!\n");
            else
                printf("Player %d wins!\n", current);
            break;
        }

        if (board_is_full(&board)) {
            printf("Board is full — draw!\n");
            break;
        }

        current = (current == 1) ? 2 : 1;
    }
}
