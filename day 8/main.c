#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Point {
    int x;
    int y;
};

struct PointList {
    int size;
    int capacity;
    struct Point* ptr;
};

int main() {
    int capacity = 16;
    // int width = 12; // sample input width
    int width = 50; // actual input width
    int idx = 0;
    char** grid = malloc(capacity * sizeof(char*));
    while (1) {
        char* buffer = NULL;
        int read;
        size_t len;
        read = getline(&buffer, &len, stdin);
        if (-1 != read) {
            // how do we determine width??
            grid[idx++] = buffer;
        }
        else {
            break;
        }

        // expand grid rows if needed
        if (idx == capacity) {
            capacity *= 2;
            grid = realloc(grid, capacity * sizeof(char*));
        }
    }

    // declare and initialize space for tracking where antinodes are
    char evil[idx][width];
    char evil2[idx][width];
    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < width; j++) {
            evil[i][j] = 0;
            evil2[i][j] = 0;
        }
    }

    struct PointList frequencies[256];
    for (int i = 0; i < 256; i++) {
        frequencies[i].ptr = malloc(10 * sizeof(struct Point));
        if (frequencies[i].ptr == NULL) {
            printf("ERROR ALLOCATING MEMORY FOR FREQUENCY %c", i);
            return 1;
        }
        frequencies[i].size = 0;
        frequencies[i].capacity = 10;
    }

    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char c = grid[i][j];
            if (c == '.') {
                continue;
            }
            struct PointList* list = &frequencies[c];
            if (list->size > list->capacity) {
                list->capacity *= 2;
                list->ptr = realloc(list->ptr, list->capacity);
            }
            struct Point* point = &list->ptr[list->size++];
            point->y = i;
            point->x = j;
        }
    }

    int total = 0;
    int total2 = 0;
    for (int freq = 0; freq < 256; freq++) {
        struct PointList* list = &frequencies[freq];
        if (list->size == 0) {
            continue;
        }

        for (int ant1 = 0; ant1 < list->size; ant1++) {
            for (int ant2 = 0; ant2 < list->size; ant2++) {
                if (ant1 == ant2)
                    continue;
                const struct Point* p1 = &list->ptr[ant1];
                const struct Point* p2 = &list->ptr[ant2];

                // part 1
                int endX = 2 * p1->x - p2->x;
                int endY = 2 * p1->y - p2->y;
                if (evil[endY][endX] != 1) {
                    if (!(endX < 0 || endY < 0 || endX >= width || endY >= idx)) {
                        evil[endY][endX] = 1;
                        total++;
                    }
                }

                /*
                part 2 - start at antenna p2 and find every place
                in line with both p1 and p2 that doesn't have an antinode yet
                */
                endX = p2->x;
                endY = p2->y;
                while (!(endX < 0 || endY < 0 || endX >= width || endY >= idx)) {
                    if (evil2[endY][endX] != 1) {
                        evil2[endY][endX] = 1;
                        total2++;
                    }
                    endY += p1->y - p2->y;
                    endX += p1->x - p2->x;
                }
            }
        }
    }

    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < width; j++) {
            printf("%c", evil[i][j] ? 'X' : (evil2[i][j] ? '#' : '.'));
        }
        printf("\n");
    }
    printf("Part 1 total: %d\n", total);
    printf("Part 2 total: %d\n", total2);
    return 0;
}
