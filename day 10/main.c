#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct PathValue
{
    char height;
    int src;
};

struct PointNode
{
    int x;
    int y;
    int src;
    struct PointNode *next;
};

int checkDir(struct PointNode point, int dx, int dy, struct PathValue *map, int width, int height, struct PointNode **list);
struct PointNode *addNode(struct PointNode *list, int x, int y, int src);

int main()
{
    char buffer[200];
    int capacity = 16;
    int size = 0;
    struct PathValue *map = malloc(capacity * sizeof(struct PathValue));
    struct PointNode *points = malloc(sizeof(struct PointNode));
    points->next = NULL;

    int width = 0;
    int height = 0;
    while (1)
    {
        char *a = fgets(buffer, sizeof(buffer), stdin);
        if (a)
        {
            int len = strlen(a) - 1;
            if (!width)
            {
                width = len;
            }
            if (len == 0)
            {
                break;
            }
            for (int i = 0; i < width; i++)
            {
                struct PathValue *pv = &map[size++];
                pv->height = a[i] - '0';
                pv->src = 0;

                if (pv->height == 0)
                {
                    points = addNode(points, i, height, height * width + i);
                }

                if (size >= capacity)
                {
                    capacity *= 2;
                    map = realloc(map, capacity * sizeof(struct PathValue));
                    if (map == NULL)
                    {
                        printf("Error expanding memory for map!");
                        return 1;
                    }
                }
            }
            height++;
        }
        else
        {
            break;
        }
    }

    int part1 = 0;
    int part2 = 0;
    while (points->next != NULL)
    {
        struct PointNode *point = points;
        points = points->next;
        int a;
        a = checkDir(*point, 0, 1, map, width, height, &points);
        part1 += a == 1;
        part2 += a >= 1;

        a = checkDir(*point, 1, 0, map, width, height, &points);
        part1 += a == 1;
        part2 += a >= 1;

        a = checkDir(*point, 0, -1, map, width, height, &points);
        part1 += a == 1;
        part2 += a >= 1;

        a = checkDir(*point, -1, 0, map, width, height, &points);
        part1 += a == 1;
        part2 += a >= 1;
        free(point);
    }

    printf("Part 1: %d\n", part1);
    printf("Part 2: %d\n", part2);
    return 0;
}

int checkDir(struct PointNode point, int dx, int dy, struct PathValue *map, int width, int height, struct PointNode **list)
{
    int x = point.x;
    int y = point.y;
    int src = point.src;
    if (x + dx < 0 || y + dy < 0 || x + dx >= width || y + dy >= height)
    {
        return 0;
    }

    struct PathValue *pv = &map[y * width + x];
    struct PathValue *nextPv = &map[(y + dy) * width + x + dx];
    int notUnique = 0;
    if (nextPv->height == pv->height + 1)
    {
        *list = addNode(*list, x + dx, y + dy, src);
        notUnique = nextPv->src == src;
        nextPv->src = src;
    }
    else
    {
        return 0;
    }

    if (nextPv->height != 9)
        return 0;
    return (nextPv->height == 9) + (notUnique);
}

struct PointNode *addNode(struct PointNode *list, int x, int y, int src)
{
    struct PointNode *newNode = malloc(sizeof(struct PointNode));
    newNode->next = list;
    newNode->x = x;
    newNode->y = y;
    newNode->src = src;
    return newNode;
}