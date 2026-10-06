/* rocket_launch.c – Professional version
 * Clean, smooth ASCII animation of a rocket launch.
 * Compile: gcc -Wall -Wextra -std=c11 -o rocket rocket_launch.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HEIGHT     22          /* visible rows */
#define WIDTH      60
#define ROCKET_H   8           /* height of the rocket drawing */
#define MAX_FRAMES 18

/* Portable millisecond delay */
void delay(int ms) {
    clock_t start = clock();
    while (clock() < start + (ms * CLOCKS_PER_SEC) / 1000)
        ;
}

/* Clear screen using ANSI escape codes (works on Windows Terminal,
   macOS, Linux, and most modern terminals) */
void clear_screen(void) {
    printf("\033[2J\033[H");
    fflush(stdout);
}

/* Simple starfield – some stars twinkle based on frame number */
void draw_stars(int frame) {
    /* Fixed star positions for a clean look */
    const int stars[][2] = {
        {2,5},{3,18},{1,32},{4,47},{2,55},
        {6,9},{5,27},{7,41},{6,52},
        {9,3},{10,22},{8,38},{11,49},
        {13,14},{12,33},{14,45},{15,7},
        {17,25},{16,51},{18,12},{19,39}
    };
    int n = sizeof(stars) / sizeof(stars[0]);

    for (int i = 0; i < n; i++) {
        int y = stars[i][0];
        int x = stars[i][1];
        /* Twinkle: occasionally show a brighter star */
        char c = ((frame + i) % 7 == 0) ? '+' : '.';
        if (y < HEIGHT - 3) {          /* keep stars above the ground */
            printf("\033[%d;%dH%c", y + 1, x + 1, c);
        }
    }
}

void draw_ground(void) {
    /* Launch pad / ground */
    printf("\033[%d;1H", HEIGHT - 1);
    for (int i = 0; i < WIDTH; i++) putchar('=');
    printf("\033[%d;1H", HEIGHT);
    printf("   LAUNCH PAD          [READY]          MISSION CONTROL");
}

void draw_rocket(int base_row) {
    /* base_row is the row where the bottom of the rocket sits */
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
    /* Animated exhaust – changes every frame */
    const char *flames[] = {
        "      vWvWv     ",
        "      WvWvW     ",
        "      vWvWv     ",
        "     \\vWvWv/    ",
        "     /WvWvW\\    "
    };
    int idx = frame % 5;
    int row = base_row + 1;

    if (row >= 1 && row <= HEIGHT - 2) {
        printf("\033[%d;%dH%s", row, (WIDTH - 16) / 2, flames[idx]);
    }
    /* Extra lower flame for bigger effect */
    if (row + 1 <= HEIGHT - 2) {
        printf("\033[%d;%dH   ~~~~~   ", row + 1, (WIDTH - 16) / 2 + 3);
    }
}

int main(void) {
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

    /* Main animation loop – rocket rises */
    for (int frame = 0; frame < MAX_FRAMES; frame++) {
        clear_screen();

        /* Calculate rocket position (starts near bottom, moves up) */
        int ground_level = HEIGHT - 2;
        int progress = frame;                  /* 0 … MAX_FRAMES-1 */
        int base_row = ground_level - (progress * (HEIGHT - ROCKET_H - 4)) / (MAX_FRAMES - 1);

        draw_stars(frame);
        draw_ground();
        draw_rocket(base_row);
        draw_flames(base_row, frame);

        /* Small status line */
        printf("\033[%d;1H  ALTITUDE: %3d m     SPEED: %3d m/s     STATUS: ASCENDING",
               HEIGHT, progress * 120, 80 + progress * 15);

        delay(280);        /* smooth ~3–4 fps feel */
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

    printf("\n\nPress Enter to exit...");
    fflush(stdout);
    getchar();

    return 0;
}