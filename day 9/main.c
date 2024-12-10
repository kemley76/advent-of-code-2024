#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct MemoryBlock
{
    int idx;
    int id;
    int size;
};

int main()
{
    char x;
    int capacity = 512;
    int size = 0;
    struct MemoryBlock *disk = malloc(capacity * sizeof(struct MemoryBlock));
    int diskSize = 0;
    // Input processing
    while (scanf("%c", &x) != EOF)
    {
        char value = x - '0';
        struct MemoryBlock *block = &disk[size++];
        block->id = size / 2;
        block->size = value;
        block->idx = diskSize;
        diskSize += value;
        if (size >= capacity)
        {
            capacity *= 2;
            disk = realloc(disk, capacity * sizeof(struct MemoryBlock));
            if (disk == NULL)
            {
                printf("UNABLE TO ALLOCATE %ld BYTES FOR DISK", capacity * sizeof(char));
                return 1;
            }
        }
    }

    // Part 1: Move the blocks into any available gaps
    long int part1 = 0;
    int rightIdx = size - 1;
    int pos = 0;
    struct MemoryBlock *right = &disk[rightIdx];
    int rightRemaining = right->size;
    for (int leftIdx = 0; leftIdx < size; leftIdx += 2)
    {
        struct MemoryBlock *left = &disk[leftIdx];
        struct MemoryBlock *gap = &disk[leftIdx + 1];

        // only can happen on the last loop
        if (right == left)
        {
            for (int i = 0; i < rightRemaining; i++)
            {
                part1 += right->id * (pos++);
            }
            break;
        }

        // add the left block to the total
        for (int j = 0; j < left->size; j++)
        {
            part1 += left->id * (pos++);
        }

        // fill in the gap with file blocks from the right end
        while (gap->size > 0)
        {
            part1 += right->id * (pos++);
            gap->size--; // track how much space is left in the block
            rightRemaining--;
            // start using the next unmoved block available on the right
            if (rightRemaining == 0)
            {
                rightIdx -= 2;
                if (rightIdx <= leftIdx)
                {
                    goto done;
                }
                right = &disk[rightIdx];
                rightRemaining = right->size;
            }
        }
    }
done:

    // reset the gap sizes
    for (int i = 1; i < size; i += 2)
    {
        struct MemoryBlock *next = &disk[i + 1];
        struct MemoryBlock *gap = &disk[i];
        gap->size = next->idx - gap->idx;
    }

    // Part 2: Move the blocks only to gaps that can fit the entire block
    // start from the right most block and go left through all the blocks
    for (int i = size - 1; i >= 0; i -= 2)
    {
        struct MemoryBlock *memBlock = &disk[i];
        // search through available gaps and place current block
        // into first gap that fits
        for (int j = 1; j < size; j += 2)
        {
            struct MemoryBlock *gapBlock = &disk[j];

            // do not move any blocks to the right
            if (memBlock->idx < gapBlock->idx)
                break;

            // found a gap that fits
            if (gapBlock->size >= memBlock->size)
            {
                memBlock->idx = gapBlock->idx;
                gapBlock->idx += memBlock->size;
                gapBlock->size -= memBlock->size;
                break;
            }
        }
    }

    // use the new block indices to compute the total
    long int part2 = 0;
    for (int i = 0; i < size; i += 2)
    {
        struct MemoryBlock *memBlock = &disk[i];
        for (int j = 0; j < memBlock->size; j++)
        {
            part2 += memBlock->id * (memBlock->idx + j);
        }
    }

    printf("Part 1: %ld\n", part1);
    printf("Part 2: %ld\n", part2);
    return 0;
}