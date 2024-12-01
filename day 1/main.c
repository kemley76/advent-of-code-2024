#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void heapify(int*, int);
void swap(int*, int*);
void heapifyDown(int*, int, int);

int main() {
    int capacity = 16;
    int size = 0;

    int* leftList = malloc(capacity * sizeof(int));
    int* rightList = malloc(capacity * sizeof(int));

    int left, right;
    while (scanf("%d %d", &left, &right) != EOF) {
        leftList[size] = left;
        rightList[size] = right;
        size++;
        if (size == capacity) {
            capacity *= 2;
            leftList = realloc(leftList, capacity * sizeof(int));
            rightList = realloc(rightList, capacity * sizeof(int));
        }
    }
    heapify(leftList, size);
    heapify(rightList, size);

   int totalDifference = 0;
    while (size > 0) {
        totalDifference += abs(leftList[0] - rightList[0]);

        swap(leftList, leftList + size - 1);
        swap(rightList, rightList + size - 1);
        size--;
        heapifyDown(rightList, 0, size);
        heapifyDown(leftList, 0, size);
    }
    printf("Total difference: %d\n", totalDifference);

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

void swap(int* a, int* b) {
    int temp = *a; 
    *a = *b;
    *b = temp;
}