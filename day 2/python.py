import math
import sys

def check(arr):
    pairs = [(arr[i], arr[i + 1]) for i in range(len(arr) - 1)]
    gt = [x[0] > x[1] for x in pairs]
    asc = all(gt)
    dsc = all([not x for x in gt])
    rng = all([abs(x[0] - x[1]) >= 1 and abs(x[0] - x[1]) <= 3 for x in pairs])
    return (asc or dsc) and rng

count = 0
while True:
    try:
        r = list(map(int, input().split()))
        # Process the line
        if check(r):
            count += 1
            continue
        for i in range(len(r)):
            cpy = r.copy()
            del cpy[i]
            print(cpy)
            if check(cpy):
                count += 1
                break

    except EOFError:
        break  # Exit loop on EOF
print(count)