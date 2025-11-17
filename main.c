#include <stdio.h>
#include "game.h"

int main(void) {
    printf("Welcome to Connect Four!\n");
    
    int play_again = 1;
    while (play_again) {
        game_run();
        
        printf("\nPlay again? (1=Yes, 0=No): ");
        int choice;
        if (scanf("%d", &choice) == 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            play_again = (choice == 1);
        } else {
            play_again = 0;
        }
    }
    
    printf("Thanks for playing Connect Four!\n");
    return 0;
}
