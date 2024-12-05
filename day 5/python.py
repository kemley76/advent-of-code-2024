def topSort(pages, prereqs):
    counts = {a: 0 for a in pages}
    for a, b in prereqs:
        counts[b] += 1 
    
    sort = []
    queue = []
    for key in counts:
        if counts[key] == 0:
            queue.append(key)
    
    while len(queue) > 0:
        v = queue.pop()
        sort.append(v)
        for a, b in prereqs:
            if a == v:
                counts[b] -= 1
                if counts[b] == 0:
                    queue.append(b)
    return sort

count = 0
# process pages
ordering = set()
while True:
    try:
        l = input()
        if l == '':
            break
        left, right = l.split('|')
        ordering.add((int(left), int(right)))

    except EOFError:
        break  # Exit loop on EOF

total = 0
wrongTotal = 0
while True:
    try:
        l = input()
        pages = list(map(int, l.split(',')))
        prereqs = set()
        for a, b in ordering:
            if a not in pages or b not in pages:
                continue
            prereqs.add((a, b))

        for a, b in prereqs:
            aIdx = pages.index(a)
            bIdx = pages.index(b)
            if aIdx > bIdx:
                break
        else:
            total += pages[len(pages)//2]
            continue
        
        # ordering is wrong and it needs to be sorted
        sortedPages = topSort(pages, prereqs)
        wrongTotal += sortedPages[len(sortedPages)//2]

    
    except EOFError:
        break  # Exit loop on EOF

print(total)
print(wrongTotal)