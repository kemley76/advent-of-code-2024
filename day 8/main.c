#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point {
    int x;
    int y;
};

int main() {
    printf("Hello World!\n");
    int capacity = 500;
    //int width = 12;
    int width = 50;
    int idx = 0;
    char** grid = malloc(capacity * sizeof(char*));
    while (1) {
        char *buffer = NULL;
        int read;
        size_t len;
        read = getline(&buffer, &len, stdin);
        if (-1 != read) {
            // how do we determine width??
            //char* row = malloc(width * sizeof(char));
            //memcpy(row, buffer, len);
            //free(buffer);
            grid[idx++] = buffer;
            printf("Hello %c", grid[idx - 1][0]);
        } else {
            break;
        }
        if (idx == capacity) {
            capacity *= 2;
            grid = realloc(grid, capacity * sizeof(char*));
        }
    }

    char evil[idx][width];
    char evil2[idx][width];
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            evil[i][j] = 0;
            evil2[i][j] = 0;
        }
    }
    //evil = malloc(width * idx * sizeof(char));
    struct Point* frequencies[256];
    unsigned char counts[256];
    unsigned char sizes[256];
    for (int i = 0; i < 256; i++) {
        frequencies[i] = malloc(10 * sizeof(struct Point));
        counts[i] = 0;
        sizes[i] = 10;
    }

    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char c = grid[i][j];
            if (c == '.') {
                continue;
            }
            if (counts[c] >= sizes[c]) {
                sizes[c] *= 2;
                frequencies[c] = realloc(frequencies[c], sizes[c]);
            } 
            struct Point *point = &frequencies[c][counts[c]++];
            point->y = i;
            point->x = j;
            printf("(%d, %d) %d %c\n", point->x, i, counts[c], (char)c);
        }
    }

    int total = 0;
    int total2 = 0;
    for (int freq = 0; freq < 256; freq++) {
        if (counts[freq] == 0) {
            continue;
        }

        printf("\nFrequency: %c\n", freq);
        for (int ant1 = 0; ant1 < counts[freq]; ant1++) {
            for (int ant2 = 0; ant2 < counts[freq]; ant2++) {
                if (ant1 == ant2)
                    continue;
                struct Point p1 = frequencies[freq][ant1];
                struct Point p2 = frequencies[freq][ant2];
                int endX = 2 * p1.x - p2.x;
                int endY = 2 * p1.y - p2.y;
                if (evil[endY][endX] != 1) {
                    if (!(endX < 0 || endY < 0 || endX >= width || endY >= idx)) {
                        evil[endY][endX] = 1;
                        total++;
                    }
                }
                endX = p2.x;
                endY = p2.y;
                while (!(endX < 0 || endY < 0 || endX >= width || endY >= idx)) {
                    if (evil2[endY][endX] != 1) {
                        evil2[endY][endX] = 1;
                        total2++;
                    }
                    endY += p1.y - p2.y;
                    endX += p1.x - p2.x;
                }
                //printf("(%d, %d) & (%d, %d) -> %d %d\n", p1.x, p1.y, p2.x, p2.y, endX, endY);
            }
        }
    }
    int newCount = 0;
    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < width; j++) {
            if (evil[i][j] == 1) {
                newCount++;
                printf("0");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    printf("Total: %d\n", total);
    printf("Total2: %d\n", total2);
    printf("Idx: %d\n", idx);
    printf("Net tot: %d\n", newCount);
    return 0;
}
