search = []
total = 0
area = []
while True:
    try:
        area.append(list(input()))

    except EOFError:
        break  # Exit loop on EOF

dIdx = 0
directions = [(0, -1), (1, 0), (0, 1), (-1, 0)]
count = 1
for y in range(len(area)):
    for x in range(len(area[0])):
        if area[y][x] == '^':
           area[y][x] = 'X'
           cx, cy, startX, startY = x, y, x, y

print(cx, cy)
initialPath = set()
while cx >= 0 and cy >= 0 and cy < len(area) and cx < len(area[0]):
    dx, dy = directions[dIdx]
    try:
        if area[cy + dy][cx + dx] == '#':
            dIdx = (dIdx + 1) % 4
            continue
    except IndexError:
        count += 1
        break

    if area[cy][cx] != 'X':
        count += 1
        area[cy][cx] = 'X'
    cx += dx
    cy += dy
    initialPath.add((cx, cy))

directionFlags = [0b0001, 0b0010, 0b0100, 0b1000]

loopCount = 0
print(len(initialPath))
blah = 0
obstacles = []
for x, y in initialPath:
    #print(x, y)
    blah+= 1
    print(blah)
    dIdx = 0
    cx = startX
    cy = startY
    if cx == x and cy == y:
        continue

    # reconstruct area with new obstacle
    newArea = []
    nowY = 0
    for l in area:
        row = [] 
        nowX = 0
        for c in l:
            if c == '#' or (nowX == x and nowY == y):
                row.append('#')
            else: 
                row.append(0b0000)
            nowX += 1
        newArea.append(row)
        nowY += 1

    # traverse path with new obstacles
    while cx >= 0 and cy >= 0 and cy < len(area) and cx < len(area[0]):
        dx, dy = directions[dIdx]
        if cy + dy < 0 or cx + dx < 0:
            break
        try:
            if newArea[cy + dy][cx + dx] == '#':
                dIdx = (dIdx + 1) % 4
                continue
        except IndexError:
            break

        if (newArea[cy][cx] & directionFlags[dIdx]) != 0:
            loopCount += 1
            obstacles.append((x, y))
            break
        newArea[cy][cx] |= directionFlags[dIdx]
        cx += dx
        cy += dy

print(count)
#for y, l in enumerate(area):
    #for x, c in enumerate(l):
        #if c == '#': 
            #print('#', end='')
        #elif (x, y) in obstacles or (x == 7 and y == 9):
            #print('0', end='')
        #else:
            #print('.', end='')
    #print()
print(initialPath)

#print("area: ")
#for l in area:
    #print(*l, sep='')

print("loops: ", loopCount)