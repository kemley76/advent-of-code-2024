#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Plot
{
    int area;
    int perimiter;
    int sides;
};

struct Plot search(char **grid, int x, int y, int width, int height);

int main()
{
    printf("Hello World!\n");

    unsigned int capacity = 16;
    // int width = 10; // sample input width
    int width = 140; // actual input width
    unsigned int idx = 0;
    char **grid = malloc(capacity * sizeof(int *));
    while (1)
    {
        char *buffer = NULL;
        long int read;
        size_t len;
        read = getline(&buffer, &len, stdin);
        if (-1 != read)
        {
            // how do we determine width??
            grid[idx++] = buffer;
        }
        else
        {
            break;
        }

        // expand grid rows if needed
        if (idx == capacity)
        {
            capacity *= 2;
            grid = realloc(grid, capacity * sizeof(char *));
        }
    }

    int part1 = 0;
    int part2 = 0;

    for (unsigned int i = 0; i < idx; i++)
    {
        for (int j = 0; j < width; j++)
        {
            struct Plot plot = search(grid, j, (int)i, width, (int)idx);
            part1 += plot.area * plot.perimiter;
            part2 += plot.area * plot.sides;
            if (plot.area != 0)
                printf("%d * %d = %d\n", plot.area, plot.sides, plot.area * plot.sides);
        }
    }

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);
    return 0;
}

struct Plot search(char **grid, int x, int y, int width, int height)
{
    struct Plot plot;
    int here = grid[y][x];
    grid[y][x] |= (char)0b10000000;
    if (here >> 7 != 0)
    {
        plot.area = 0;
        plot.perimiter = 0;
        plot.sides = 0;
        return plot;
    }

    plot.area = 1;
    plot.perimiter = 0;
    plot.sides = 0;

    char mask = 0b1111111;
    int up = y == 0 || (grid[y - 1][x] & mask) != here;
    int left = x == 0 || (grid[y][x - 1] & mask) != here;
    int down = y == height - 1 || (grid[y + 1][x] & mask) != here;
    int right = x == width - 1 || (grid[y][x + 1] & mask) != here;

    int upLeft = y == 0 || x == 0 || (grid[y - 1][x - 1] & mask) != here;
    int upRight = y == 0 || x == width - 1 || (grid[y - 1][x + 1] & mask) != here;
    int downLeft = y == height - 1 || x == 0 || (grid[y + 1][x - 1] & mask) != here;
    int downRight = y == height - 1 || x == width - 1 || (grid[y + 1][x + 1] & mask) != here;

    if (up)
    {
        plot.perimiter++;
    }
    else
    {
        struct Plot next = search(grid, x, y - 1, width, height);
        plot.area += next.area;
        plot.perimiter += next.perimiter;
        plot.sides += next.sides;
    }
    if (left)
    {
        plot.perimiter++;
    }
    else
    {
        struct Plot next = search(grid, x - 1, y, width, height);
        plot.area += next.area;
        plot.perimiter += next.perimiter;
        plot.sides += next.sides;
    }
    if (down)
    {
        plot.perimiter++;
    }
    else
    {
        struct Plot next = search(grid, x, y + 1, width, height);
        plot.area += next.area;
        plot.perimiter += next.perimiter;
        plot.sides += next.sides;
    }
    if (right)
    {
        plot.perimiter++;
    }
    else
    {
        struct Plot next = search(grid, x + 1, y, width, height);
        plot.area += next.area;
        plot.perimiter += next.perimiter;
        plot.sides += next.sides;
    }

    if (up && left)
        plot.sides++;
    if (up && right)
        plot.sides++;
    if (down && right)
        plot.sides++;
    if (down && left)
        plot.sides++;

    if (left)
    {
        if (!upLeft && !up)
            plot.sides++;
        if (!downLeft && !down)
            plot.sides++;
    }

    if (right)
    {
        if (!upRight && !up)
            plot.sides++;
        if (!downRight && !down)
            plot.sides++;
    }
    return plot;
}
