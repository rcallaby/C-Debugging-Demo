/* rocket_launch.c – INTENTIONALLY BUGGY (all 10 classic errors)
 * Fix every bug to obtain the professional smooth animation.
 */

#include <stdio.h>
/* BUG 1: Missing headers → undeclared malloc, strcpy, free, etc. */
#include <time.h>

#define HEIGHT     22
#define WIDTH      60
#define ROCKET_H   8
#define MAX_FRAMES 18

void delay(int ms) {
    clock_t start = clock();
    while (clock() < start + (ms * CLOCKS_PER_SEC) / 1000)
        ;
}

void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

void draw_stars(int frame) {
    const int stars[][2] = {
        {2,5},{3,18},{1,32},{4,47},{2,55},
        {6,9},{5,27},{7,41},{6,52},
        {9,3},{10,22},{8,38},{11,49},
        {13,14},{12,33},{14,45},{15,7},
        {17,25},{16,51},{18,12},{19,39}
    };
    int n = sizeof(stars) / sizeof(stars[0]);

    for (int i = 0; i <= n; i++) {               /* BUG 5: off-by-one (should be < n) */
        int y = stars[i][0];
        int x = stars[i][1];
        char c = ((frame + i) % 7 == 0) ? '+' : '.';
        if (y < HEIGHT - 3) {
            printf("\033[%d;%dH%c", y + 1, x + 1, c);
        }
    }
}

void draw_ground(void) {
    printf("\033[%d;1H", HEIGHT - 1);
    for (int i = 0; i < WIDTH; i++) putchar('=');
    printf("\033[%d;1H", HEIGHT);
    printf("   LAUNCH PAD          [READY]          MISSION CONTROL");
}

void draw_rocket(int base_row) {
    const char *rocket[] = {
        "       /\\       ",
        "      /  \\      ",
        "     /====\\     ",
        "     |    |     ",
        "     |    |     ",
        "     |    |     ",
        "    /|    |\\    ",
        "   /_|____|_\\   "
    };

    for (int i = 0; i < ROCKET_H; i++) {
        int row = base_row - ROCKET_H + 1 + i;
        if (row >= 1 && row <= HEIGHT - 2) {
            printf("\033[%d;%dH%s", row, (WIDTH - 16) / 2, rocket[i]);
        }
    }
}

void draw_flames(int base_row, int frame) {
    const char *flames[] = {
        "      vWvWv     ",
        "      WvWvW     ",
        "      vWvWv     ",
        "     \\vWvWv/    ",
        "     /WvWvW\\    "
    };
    int idx = frame % 5;
    int row = base_row + 1;

    /* BUG 5 continued: missing bounds check → possible out-of-bounds write */
    printf("\033[%d;%dH%s", row, (WIDTH - 16) / 2, flames[idx]);
    printf("\033[%d;%dH   ~~~~~   ", row + 1, (WIDTH - 16) / 2 + 3);
}

int main(void) {
    int frame;                                   /* BUG 4: uninitialized variable */

    printf("=== PROFESSIONAL ROCKET LAUNCH SIMULATOR ===\n\n");
    printf("Starting countdown in 2 seconds...\n");
    delay(2000);

    /* Countdown */
    for (int c = 3; c >= 1; c--) {
        clear_screen();
        printf("\n\n\n\n\n\n\n\n");
        printf("                    T-MINUS %d\n", c);
        printf("\n                 ALL SYSTEMS GO");
        delay(900);
    }

    clear_screen();
    printf("\n\n\n\n\n\n\n\n");
    printf("                     LIFTOFF!\n");
    delay(800);

    /* BUG 6 + 7: buffer overflow + bad null handling */
    char *status = malloc(16);                   /* deliberately too small */
    if (status == NULL) {
        /* incomplete – program may continue with NULL pointer */
    }
    strcpy(status, "All systems nominal - go for launch! Telemetry locked."); /* overflow */

    /* Main animation loop */
    /* BUG 8: infinite loop – missing increment / wrong condition */
    for (frame = 0; frame < MAX_FRAMES; ) {      /* no frame++ here */

        clear_screen();

        int ground_level = HEIGHT - 2;
        int progress = frame;

        /* BUG 9: integer-division subtlety – wrong altitude calculation */
        int base_row = ground_level - (progress * (HEIGHT - ROCKET_H - 4)) / MAX_FRAMES;
        /* (should be / (MAX_FRAMES - 1) and properly ordered to avoid early truncation) */

        if (base_row = 5) {                      /* BUG 3: = instead of == */
            /* this assignment always happens and changes the value */
        }

        draw_stars(frame);
        draw_ground();
        draw_rocket(base_row);
        draw_flames(base_row, frame);

        printf("\033[%d;1H  ALTITUDE: %3d m     SPEED: %3d m/s     STATUS: ASCENDING",
               HEIGHT, progress * 120, 80 + progress * 15);

        delay(280);

        /* BUG 2: syntax error – missing semicolon (cascading errors) */
        frame = frame + 1
    }

    /* Final success screen */
    clear_screen();
    printf("\n\n");
    printf("          ★★★  MISSION SUCCESS  ★★★\n\n");
    printf("               ORBIT ACHIEVED\n\n");
    printf("        .  *    .   *     .   *\n");
    printf("     *     ___          *\n");
    printf("       .  /   \\   .         *\n");
    printf("    *    | EARTH |     .\n");
    printf("       .  \\___/     *     .\n");
    printf("     *       .         *\n\n");
    printf("   Telemetry: Nominal    Crew: Safe    Payload: Deployed\n\n");
    printf("   Thank you for flying with us.\n");

    /* BUG 10: memory mismanagement – free the wrong pointer */
    free(stars);     /* stars is not a heap pointer – undefined behavior */
    /* (status is never freed → memory leak) */

    printf("\n\nPress Enter to exit...");
    fflush(stdout);
    getchar();

    return 0;
}   /* BUG 2 continued: the missing } from earlier would cascade here,
       but we keep one clear missing-semicolon example above */