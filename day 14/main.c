#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

struct Robot
{
    int px;
    int py;
    int qx;
    int qy;
};

int main()
{
    int px, py, qx, qy;

    int width = 101;
    int height = 103;
    // int width = 11;
    // int height = 7;

    long quad[4] = {0, 0, 0, 0};
    struct Robot *robots = malloc(500 * sizeof(struct Robot));
    int size = 0;
    while (scanf("p=%d,%d v=%d,%d\n", &px, &py, &qx, &qy) != EOF)
    {
        struct Robot *bot = &robots[size++];
        bot->px = px;
        bot->py = py;
        bot->qx = qx;
        bot->qy = qy;

        for (int i = 0; i < 100; i++)
        {
            px += qx;
            py += qy;
            if (px < 0)
                px += width;
            if (py < 0)
                py += height;
        }
        px = px % width;
        py = py % height;

        int left = px < width / 2;
        int right = px > width / 2;
        int up = py < height / 2;
        int down = py > height / 2;
        if (!(left || right) || !(up || down))
            continue;

        quad[up * 2 + left]++;
    }
    long part1 = 1;
    int part2;
    for (int i = 0; i < 4; i++)
    {
        part1 *= quad[i];
    }

    int grid[height][width];
    for (int i = 0; i < 100000; i++)
    {
        int inARow = 0;
        int found = 0;
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (grid[y][x] == 1)
                {
                    inARow++;
                    if (inARow == 10)
                    {
                        found = 1;
                    }
                }
                else
                {
                    inARow = 0;
                }
            }
        }

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                if (found)
                {
                    if (grid[y][x])
                        printf("X");
                    else
                        printf(".");
                }
                grid[y][x] = 0;
            }
            if (found)
                printf("\n");
        }

        if (found)
        {
            part2 = i;
            break;
        }

        for (int j = 0; j < size; j++)
        {
            struct Robot *bot = &robots[j];
            bot->px += bot->qx;
            bot->py += bot->qy;
            if (bot->px < 0)
                bot->px += width;
            if (bot->py < 0)
                bot->py += height;
            bot->px %= width;
            bot->py %= height;
            grid[bot->px][bot->py] = 1;
        }
    }
    printf("Part 1: %ld\n", part1);
    printf("Part 2: %d\n", part2);
    return 0;
}
