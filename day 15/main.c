#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int push(char** grid, int x, int y, int dx, int dy);

int main() {
    printf("Hello World!\n");

    unsigned long capacity = 16;
    int width = 120; // actual input width
    //int width = 10; 
    int idx = 0;
    char **grid = malloc(capacity * sizeof(int *));
    int x;
    int y;
    while (1)
    {
        char *buffer = NULL;
        long int read;
        size_t len;
        read = getline(&buffer, &len, stdin);
        if (buffer[0] != '#')  {
            printf("done here");
            break;
        }
        if (-1 != read)
        {
            // how do we determine width??
            grid[idx++] = buffer;
            for (int i = 0; i < width; i++) {
                if (buffer[i] == '@') {
                    x = i;
                    y = idx - 1;
                    break;
                }
            }
        }
        else
        {
            break;
        }

        // expand grid rows if needed
        if (idx == (int)capacity)
        {
            capacity *= 2;
            grid = realloc(grid, capacity * sizeof(char *));
        }
    }

    char move;
    while (scanf("%c", &move) != EOF) {
        int dx = 0;
        int dy = 0;
        switch (move) {
            case '>':
                dx = 1;
                break;
            case '<': 
                dx = -1;
                break;
            case '^':
                dy = -1;
                break;
            case 'v': 
                dy = 1;
                break;
            case '\n':
                continue;
        }
        if (dy == 0 && dx == 0)
            break;
        //printf("%d %d %d %d\n", x, y, dy, dx);
        if (push(grid, x, y, dx, dy)) {
            x += dx;
            y += dy;
            grid[y][x] = '@';
        }
        printf("%c\n", move);
    }

    printf("height: %d\n", idx);
    int part1 = 0;
    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < width; j++) {
            //printf("%d %d\n", i, j);
            printf("%c", grid[i][j]);
            if (grid[i][j] == 'O') {
                part1 += i * 100 + j;
            }
        }
        printf("\n");
    }

    printf("Part 1: %d\n", part1);
    return 0;
}

int push(char** grid, int x, int y, int dx, int dy) {
    //printf("%d %d %d %d\n", x, y, dy, dx);
    if (grid[y + dy][x + dx] == '#')
        return 0;

    if (grid[y + dy][x + dx] == '.') {
        grid[y + dy][x + dx] = 'O';
        grid[y][x] = '.';
        return 1;
    } else if (push(grid, x + dx, y + dy, dx, dy)) {
        grid[y + dy][x + dx] = 'O';
        grid[y][x] = '.';
        return 1;
    }
    return 0;
}
