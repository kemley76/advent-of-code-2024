#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    long ax, ay, bx, by, px, py;
    long part1 = 0;
    long part2 = 0;
    while (scanf("Button A: X+%ld, Y+%ld\nButton B: X+%ld, Y+%ld\nPrize: X=%ld, Y=%ld\n", &ax, &ay, &bx, &by, &px, &py) != EOF)
    {
        long b = (px * ay - py * ax) / (bx * ay - ax * by);
        long a = (py - b * by) / ay;

        if (a * ax + b * bx == px && a * ay + b * by == py)
        {
            part1 += a * 3 + b;
        }

        px += 10000000000000;
        py += 10000000000000;
        b = (px * ay - py * ax) / (bx * ay - ax * by);
        a = (py - b * by) / ay;

        if (a * ax + b * bx == px && a * ay + b * by == py)
        {
            part2 += a * 3 + b;
        }
    }

    printf("Part 1: %ld\n", part1);
    printf("Part 2: %ld\n", part2);
    return 0;
}
