#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void heapify(int*, int);
void swap(int*, int*);
void heapifyDown(int*, int, int);
int popHeap(int*, int);

int main() {
    int capacity = 16;
    int size = 0;

    int* lList = malloc(capacity * sizeof(int));
    int* rList = malloc(capacity * sizeof(int));

    int left, right;
    while (scanf("%d %d", &left, &right) != EOF) {
        lList[size] = left;
        rList[size] = right;
        size++;
        if (size == capacity) {
            capacity *= 2;
            lList = realloc(lList, capacity * sizeof(int));
            rList = realloc(rList, capacity * sizeof(int));
        }
    }
    heapify(lList, size);
    heapify(rList, size);

    int s = size;
    int totalDifference = 0;
    while (s > 0) {
        left = popHeap(lList, s);
        right = popHeap(rList, s);
        s--;
        totalDifference += abs(left - right);
    }

    int* lPtr = lList; 
    int* rPtr = rList;
    int similarityScore = 0;
    while (lPtr < lList + size && rPtr < rList + size) {
        while (rPtr < rList + size && *lPtr <= *rPtr) {
            if (*lPtr == *rPtr) {
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

void heapify(int* arr, int size) {
    // work from second to last level and work to root
    int level = log2((double)size) - 1;
    for (; level >=0; level--) { // loop through each level
        int i = (1 << level) - 1;
        int end = i + (1 << level);
        for (; i < end; i++) { // loop through each node in that level
            heapifyDown(arr, i, size);
        }
    } 
}

void heapifyDown(int* arr, int i, int size) {
    while (i * 2 + 1 < size) { // heapify down 
        int lIdx = i * 2 + 1;
        int rIdx = i * 2 + 2;
        
        int smallIdx = i; // index of the smallest value of the 3
        if (arr[smallIdx] > arr[lIdx]) {
            smallIdx = lIdx;
        }

        if (rIdx < size && arr[smallIdx] > arr[rIdx]) {
            smallIdx = rIdx;
        }

        if (smallIdx == i) {
            break;
        }

        swap(arr + smallIdx, arr + i);
        i = smallIdx;
    }
}

int popHeap(int* heap, int size) {
    int smallest = heap[0];
    swap(heap, heap + size - 1);
    heapifyDown(heap, 0, size - 1);
    return smallest;
}

void swap(int* a, int* b) {
    int temp = *a; 
    *a = *b;
    *b = temp;
}