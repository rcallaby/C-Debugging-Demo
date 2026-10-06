/* matrix_rain.c – CLEAN, ERROR-FREE VERSION
 * Professional Matrix-style digital rain animation.
 * Compile: gcc -Wall -Wextra -std=c11 -o matrix matrix_rain.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH      50
#define HEIGHT     20
#define MAX_FRAMES 40
#define NUM_COLS   30

void delay(int ms) {
    clock_t start = clock();
    while (clock() < start + (ms * CLOCKS_PER_SEC) / 1000)
        ;
}

void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

char rand_char(int seed) {
    const char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%&*";
    return chars[seed % 66];
}

int main(void) {
    int frame = 0;

    int *drops  = malloc(NUM_COLS * sizeof(int));
    int *speeds = malloc(NUM_COLS * sizeof(int));

    if (drops == NULL || speeds == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    char *msg = malloc(80);
    if (msg == NULL) {
        free(drops);
        free(speeds);
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    strcpy(msg, "Wake up, Neo... The Matrix has you. Follow the white rabbit.");

    /* Initialize columns */
    for (int c = 0; c < NUM_COLS; c++) {
        drops[c]  = -(c % 15);
        speeds[c] = 1 + (c % 3);
    }

    printf("Initializing Matrix Rain...\n");
    delay(1000);

    /* Animation */
    for (frame = 0; frame < MAX_FRAMES; frame++) {
        clear_screen();

        for (int col = 0; col < NUM_COLS; col++) {
            int x = 2 + col * ((WIDTH - 4) / NUM_COLS);   /* correct spacing */

            for (int len = 0; len < 8; len++) {
                int y = drops[col] - len;
                if (y >= 0 && y < HEIGHT) {
                    if (len == 0)
                        printf("\033[%d;%dH\033[1;32m%c\033[0m", y + 1, x, rand_char(frame + col + len));
                    else
                        printf("\033[%d;%dH\033[32m%c\033[0m", y + 1, x, rand_char(frame + col + len));
                }
            }

            drops[col] += speeds[col];

            if (drops[col] > HEIGHT + 10)
                drops[col] = -(frame % 12);
        }

        printf("\033[%d;1H\033[37mFrame %d / %d   DIGITAL RAIN ACTIVE\033[0m",
               HEIGHT + 1, frame + 1, MAX_FRAMES);

        delay(120);
    }

    /* Success screen */
    clear_screen();
    printf("\n\n");
    printf("          ★  SYSTEM SECURE  ★\n\n");
    printf("     All anomalies eliminated.\n");
    printf("     Digital rain stabilized.\n\n");
    printf("     %s\n\n", msg);

    if (frame == MAX_FRAMES) {
        printf("     Simulation complete.\n");
    }

    free(drops);
    free(speeds);
    free(msg);

    printf("\nPress Enter to exit...");
    fflush(stdout);
    getchar();

    return 0;
}