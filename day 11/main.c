#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

typedef unsigned long long ull;
struct BinTree
{
    ull value;
    ull result;
    int n;
    struct BinTree *left;
    struct BinTree *right;
    int filled;
};

ull blink(int n, ull value, struct BinTree *tree);
struct BinTree *find(struct BinTree *current, int n, ull value, char idx);
struct BinTree *create();

int main()
{
    ull part1 = 0;
    ull part2 = 0;
    int v;
    struct BinTree *root = malloc(sizeof(struct BinTree));
    root->left = NULL;
    root->right = NULL;
    root->filled = 0;
    root->n = -1;
    while (scanf("%d", &v) != EOF)
    {
        part1 += blink(25, (ull)v, root);
        part2 += blink(75, (ull)v, root);
    }

    printf("Part 1: %llu\n", part1);
    printf("Part 2: %llu\n", part2);

    return 0;
}

ull blink(int n, ull value, struct BinTree *root)
{
    struct BinTree *entry = find(root, n, value, 1);
    if (entry->filled)
    {
        return entry->result;
    }

    entry->value = value;
    entry->n = n;
    entry->filled = 1;
    if (n == 0)
    {
        entry->result = 1;
        return 1;
    }
    n--;

    if (value == 0)
    {
        entry->result = blink(n, 1, root);
        return entry->result;
    }

    // int digits = (int)log10((double)value) + 1;
    int digits = 0;
    ull v = value;
    while (v > 0)
    {
        digits++;
        v /= 10;
    }

    if (digits % 2 == 0)
    {
        int tens = 1;
        for (int i = 0; i < digits / 2; i++)
        {
            tens *= 10;
        }
        // long tens = (int)round(pow((double)10, (double)digits/2));
        ull right = value % (ull)tens;
        ull left = value / (ull)tens;
        entry->result = blink(n, left, root) + blink(n, right, root);
        return entry->result;
    }

    entry->result = blink(n, value * 2024, root);

    return entry->result;
}

struct BinTree *find(struct BinTree *current, int n, ull value, char idx)
{
    if (value == current->value && n == current->n)
    {
        return current;
    }

    if (idx)
    {
        if (value <= current->value)
        {
            if (current->left == NULL)
            {
                current->left = create();
                return current->left;
            }
            return find(current->left, n, value, 0);
        }

        if (current->right == NULL)
        {
            current->right = create();
            return current->right;
        }
        return find(current->right, n, value, 0);
    }

    if (n <= current->n)
    {
        if (current->left == NULL)
        {
            current->left = create();
            return current->left;
        }

        return find(current->left, n, value, 1);
    }

    if (current->right == NULL)
    {
        current->right = create();
        return current->right;
    }
    return find(current->right, n, value, 1);
}

struct BinTree *create()
{
    struct BinTree *tree = malloc(sizeof(struct BinTree));
    tree->left = NULL;
    tree->right = NULL;
    tree->filled = 0;
    return tree;
}