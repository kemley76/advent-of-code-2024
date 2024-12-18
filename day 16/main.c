#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define WIDTH 141
#define HEIGHT 141

//#define WIDTH 17
//#define HEIGHT 17

struct Node {
    int score;
    int dx;
    int dy;
    int x;
    int y;
};

struct Heap
{
    struct Node node;
    struct Heap *left;
    struct Heap *right;
};

int solveMaze(char maze[HEIGHT][WIDTH], int startX, int startY, int endX, int endY);
void push(struct Heap* heap, struct Node node);
void popMin(struct Heap *root);
void heapify(struct Heap *root);
struct Node create(int score, int x, int y, int dx, int dy);
int countPath(int score[HEIGHT][WIDTH], int x, int y, int length, int endX, int endY, int cdx, int cdy, int start);

int main() {
    char grid[HEIGHT][WIDTH];
    int x, y, endX, endY;
    for (int i = 0; i < HEIGHT; i++)
    {
        // expand grid rows if needed
        char *buffer = NULL;
        size_t len;
        getline(&buffer, &len, stdin);
        for (int j = 0; j < WIDTH; j++) {
            grid[i][j] = buffer[j];
            if (buffer[j] == 'S') {
                x = j;
                y = i;
            } else if (buffer[j] == 'E') {
                endX = j;
                endY = i;
            }
        }
    }

    solveMaze(grid, x, y, endX, endY);
    return 0;
}

int solveMaze(char maze[HEIGHT][WIDTH], int startX, int startY, int endX, int endY) { 
    int score[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            score[i][j] = 0;
        }
    }

    struct Heap heap;
    heap.left = NULL;
    heap.right = NULL;
    heap.node.score = INT_MAX;
    push(&heap, create(0, startX, startY, 1, 0));
    struct Node next = heap.node;
    popMin(&heap);

    int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int bestScore = -1;
    while (1) {
        int x = next.x;
        int y = next.y;
        if (score[y][x] != 0)
            goto afterLoop;
        score[y][x] = next.score;
        for (int i = 0; i < 4; i++) {
            int dx = dirs[i][0];
            int dy = dirs[i][1];

            if (x == endX && y == endY && bestScore == -1) {
                printf("Part 1: %d\n", next.score);
                bestScore = next.score;
            }

            // cannot turn 180 degrees
            if (next.dx == -dx && next.dy == -dy) 
                continue;
            // cannot move out of bounds
            if (x + dx < 0 || y + dy < 0 || x + dx >= WIDTH || y + dy >= HEIGHT)
                continue;
            // cannot move into a wall
            if (maze[y + dy][x + dx] == '#')
                continue;

            int moveScore = 1001; // turning and moving forward
            if (next.dx == dx && next.dy == dy) {
                moveScore = 1; // going forward
            } else {
               //score[y][x] = next.score + 1000;
            }

            push(&heap, create(next.score + moveScore, x + dx, y + dy, dx, dy));
        }
        afterLoop:
        next = heap.node;
        if (bestScore != -1 && next.score > bestScore)
            break;
        popMin(&heap);
    }

    score[startY][startX] = 0;
    printf("Part 2: %d\n", countPath(score, startX, startY, 0, endX, endY, 0, 0, 1));

    int cnt = 0;
    score[startY][startX] = -1;
    score[endX][endX] = -1;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int s = score[i][j];
            if (s < 0) {
                printf("O");
                cnt += 1;
            }
            else if (s == 0)
                    printf("#");
            else
                    printf(" ");
        }
        printf("\n");
    }
    printf("Count %d\n", cnt);
    return -1;
}

struct Node create(int score, int x, int y, int dx, int dy) {
    //printf("Create!\n");
    struct Node node;
    node.score = score;
    node.x = x;
    node.y = y;
    node.dx = dx;
    node.dy = dy;
    return node;
}

void push(struct Heap* heap, struct Node node) {
    //printf("PUSH! %lx\n", (unsigned long int)heap);
    if (heap->node.score > node.score) {
        struct Node temp = heap->node; 
        //printf("done pushing %d\n", heap->node.score);
        heap->node = node;
        //printf("here!\n");
        if (heap->left == NULL) {
            heap -> left = malloc(sizeof(struct Heap));
            heap->left->node = temp;
            heap->left->left = NULL;
            heap->left->right = NULL;
        } else if (heap->right == NULL) {
            heap -> right = malloc(sizeof(struct Heap));
            heap->right->node = temp;
            heap->right->left = NULL;
            heap->right->right = NULL;
        } else {
            push(heap->left, temp);
        }
    } else {
        if (heap->left == NULL) {
            heap -> left = malloc(sizeof(struct Heap));
            heap->left->node = node;
            heap->left->left = NULL;
            heap->left->right = NULL;
        } else if (heap->right == NULL) {
            heap -> right = malloc(sizeof(struct Heap));
            heap->right->node = node;
            heap->right->left = NULL;
            heap->right->right = NULL;
        } else {
            push(heap->left, node);
        }
    }
}

void popMin(struct Heap *root)
{
    //printf("Pop Min!\n");
    root->node.score = INT_MAX;
    heapify(root);
}

void heapify(struct Heap *root) {
    struct Heap* min = root;
    if (root->left != NULL && min->node.score > root->left->node.score) {
        min = root->left;
    }
    if (root->right != NULL && min->node.score > root->right->node.score) {
        min = root->right;
    }
    if (min != root) {
        struct Node temp = root->node;
        root->node = min->node;
        min->node = temp;
        heapify(min);
    }
}

int countPath(int score[HEIGHT][WIDTH], int x, int y, int length, int endX, int endY, int cdx, int cdy, int start) {
    int total = 0;
    if (x == endX && y == endY)
        return 1;

    if (score[y][x] == 0 && !start)
        return 0;

    int s = score[y][x];

    int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 0; i < 4; i++) {
        int dx = dirs[i][0];
        int dy = dirs[i][1];
        if (cdx == -dx && cdy == -dy)
            continue;

        int next = score[y + dy][x + dx];
        if (next == 0)
            continue;
        //printf("%d len %d %d -- %d %d\n", length, x, y, s, next);
        if (next < 0 && (s == -1 * next - 1 || s == -1 * next + 999)) {
            score[y][x] = -s;
            total += 1;
            //printf("rejoin");
        } else if (next < 0) {
            //printf("end...");
            continue;
        }
        if (s == next - 1 || s == next - 1001 || s == next + 999) {
            //printf("bam\n");
            int val = countPath(score, x + dx, y + dy, length + 1, endX, endY, dx, dy, 0);
             if (val != 0) {
                score[y][x] = -s;
                total += val + 1;
            }
        } 
    }
    return total;
}