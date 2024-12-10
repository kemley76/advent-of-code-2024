/* --- Day 1: Historian Hysteria ---
Part 1: Find the sum of the absolute differences between the nth smallest
element in the left list and the nth smallest element in the right list

Part 2: Find the similarity score where for every time an element in the left
list is repeated in the right list, it iis added to the total similarity score
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void heapify(int *, int);
void swap(int *, int *);
void heapifyDown(int *, int, int);
int popHeap(int *, int);

int main()
{
    int capacity = 16; // initial capacity of heaps, expands as needed
    int size = 0;

    int *lList = malloc(capacity * sizeof(int));
    int *rList = malloc(capacity * sizeof(int));

    // collect left and right lists from stdin
    int left, right;
    while (scanf("%d %d", &left, &right) != EOF)
    {
        lList[size] = left;
        rList[size] = right;
        size++;
        if (size == capacity)
        {
            capacity *= 2;
            lList = realloc(lList, capacity * sizeof(int));
            rList = realloc(rList, capacity * sizeof(int));
        }
    }

    // turn left and right lists in to min heaps for constant time
    // removal of smallest element
    heapify(lList, size);
    heapify(rList, size);

    // Part 1
    int s = size;
    int totalDifference = 0;
    while (s > 0)
    {
        // get nth smallest elements in left and right lists
        left = popHeap(lList, s);
        right = popHeap(rList, s);
        s--;
        totalDifference += abs(left - right);
    }

    // Part 2
    // Left and right lists are now sorted in descending order after part 1
    int *lPtr = lList;
    int *rPtr = rList;
    int similarityScore = 0;
    // use two pointers to find which elements of the left list also occur in
    // the right list (and find how many times)
    while (lPtr < lList + size && rPtr < rList + size)
    {
        while (rPtr < rList + size && *lPtr <= *rPtr)
        {
            if (*lPtr == *rPtr)
            {
                similarityScore += *lPtr;
            }
            rPtr++;
        }
        lPtr++;
    }

    printf("Total difference: %d\n", totalDifference);
    printf("Similarity score: %d\n", similarityScore);

    return 0;
}

// construct a min heap from an array
void heapify(int *arr, int size)
{
    // work from second to last level and work to root
    int level = log2((double)size) - 1;
    for (; level >= 0; level--)
    { // loop through each level
        int i = (1 << level) - 1;
        int end = i + (1 << level);
        for (; i < end; i++)
        { // loop through each node in that level
            heapifyDown(arr, i, size);
        }
    }
}

// move element at index i down heap to ensure no smaller elements are below
void heapifyDown(int *arr, int i, int size)
{
    while (i * 2 + 1 < size)
    { // heapify down until complete
        int lIdx = i * 2 + 1;
        int rIdx = i * 2 + 2;

        int smallIdx = i; // index of the smallest value of the 3
        if (arr[smallIdx] > arr[lIdx])
        { // is left child smaller?
            smallIdx = lIdx;
        }

        if (rIdx < size && arr[smallIdx] > arr[rIdx])
        { // right child smaller?
            smallIdx = rIdx;
        }

        if (smallIdx == i)
        { // parent is already smallest, stop heapifying
            break;
        }

        swap(arr + smallIdx, arr + i);
        i = smallIdx;
    }
}

// returns element at top of the heap and moves to end
// re-heapifies heap to maintian structure
int popHeap(int *heap, int size)
{
    int smallest = heap[0];
    swap(heap, heap + size - 1);
    heapifyDown(heap, 0, size - 1);
    return smallest;
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}