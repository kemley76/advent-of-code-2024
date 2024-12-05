search = []
total = 0
while True:
    try:
        l = input().strip()
        search.append(l)
        print(l)

    except EOFError:
        break  # Exit loop on EOF

dirs = []
for a in range(-1, 2):
    for b in range(-1, 2):
        if not (a == 0 and b == 0):
            dirs.append((a, b))

for y in range(len(search)):
    for x in range(len(search[0])):
        for d in dirs:
            cx, cy = x, y
            dx = d[0]
            dy = d[1]
            word = ''
            for i in range(4):
                if cx < 0 or cy < 0 or cx >= len(search[0]) or cy >= len(search):
                    break
                word += search[cy][cx]
                cx += dx
                cy += dy
            if word == 'XMAS':
                total += 1

count = 0
for y in range(1, len(search) - 1):
    for x in range(1, len(search[0]) - 1):
        if search[y][x] == 'A':
            leftF = (search[y - 1][x - 1] == 'M' and search[y + 1][x + 1] == 'S')
            leftB = (search[y - 1][x - 1] == 'S' and search[y + 1][x + 1] == 'M')
            rightR = (search[y - 1][x + 1] == 'S' and search[y + 1][x - 1] == 'M')
            rightB = (search[y - 1][x + 1] == 'M' and search[y + 1][x - 1] == 'S')
            if (leftF or leftB) and (rightR or rightB):
                count += 1

print(count)