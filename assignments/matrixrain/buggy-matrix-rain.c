/* matrix_rain.c – INTENTIONALLY BUGGY
 * Contains all 10 classic high-frequency bugs.
 * Fix every one to obtain the clean digital-rain animation.
 */

#include <stdio.h>
/* BUG 1: Missing headers (stdlib.h, string.h) → undeclared malloc, strcpy, free… */
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

/* Simple deterministic “random” character */
char rand_char(int seed) {
    const char chars[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz@#$%&*";
    return chars[seed % 66];
}

int main(void) {
    int frame;                                   /* BUG 4: uninitialized variable */

    int *drops = malloc(NUM_COLS * sizeof(int)); /* will be used for column positions */
    int *speeds = malloc(NUM_COLS * sizeof(int));

    /* BUG 7: bad null-pointer handling */
    if (drops == NULL) {
        /* incomplete – continues even on failure */
    }

    /* BUG 6: buffer overflow */
    char *msg = malloc(20);
    strcpy(msg, "Wake up, Neo... The Matrix has you. Follow the white rabbit."); /* overflow */

    /* Initialize columns – contains integer-division subtlety later */
    for (int c = 0; c <= NUM_COLS; c++) {        /* BUG 5: off-by-one */
        drops[c] = -(c % 15);                    /* start above screen */
        speeds[c] = 1 + (c % 3);
    }

    printf("Initializing Matrix Rain...\n");
    delay(1000);

    /* Main animation loop */
    /* BUG 8: infinite loop (missing increment in for-header) */
    for (frame = 0; frame < MAX_FRAMES; ) {

        clear_screen();

        /* Draw rain */
        for (int col = 0; col < NUM_COLS; col++) {
            int x = 2 + col * (WIDTH / NUM_COLS);  /* BUG 9: integer-division truncation can cluster columns */

            for (int len = 0; len < 8; len++) {
                int y = drops[col] - len;
                if (y >= 0 && y < HEIGHT) {
                    /* brighter head, dimmer trail */
                    if (len == 0)
                        printf("\033[%d;%dH\033[1;32m%c\033[0m", y + 1, x, rand_char(frame + col + len));
                    else
                        printf("\033[%d;%dH\033[32m%c\033[0m", y + 1, x, rand_char(frame + col + len));
                }
            }

            drops[col] += speeds[col];

            /* reset column when it falls off screen */
            if (drops[col] > HEIGHT + 10)
                drops[col] = -(frame % 12);
        }

        /* Status line */
        printf("\033[%d;1H\033[37mFrame %d / %d   DIGITAL RAIN ACTIVE\033[0m",
               HEIGHT + 1, frame, MAX_FRAMES);

        delay(120);

        /* BUG 2: syntax error – missing semicolon (cascades) */
        frame = frame + 1
    }

    /* Final message */
    clear_screen();
    printf("\n\n");
    printf("          ★  SYSTEM SECURE  ★\n\n");
    printf("     All anomalies eliminated.\n");
    printf("     Digital rain stabilized.\n\n");
    printf("     %s\n\n", msg);

    /* BUG 3: = instead of == */
    if (frame = MAX_FRAMES) {
        printf("     Simulation complete.\n");
    }

    /* BUG 10: memory mismanagement */
    free(speeds);          /* ok */
    free(msg);             /* ok */
    free(drops + 5);       /* wrong pointer – undefined behavior */
    /* drops itself is never properly freed → leak */

    printf("\nPress Enter to exit...");
    fflush(stdout);
    getchar();

    return 0;
}