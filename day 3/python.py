import re
total = 0
exp = r"mul\((\d{1,3}),(\d{1,3})\)"
line = ''
while True:
    try:
        line += input()

    except EOFError:
        break  # Exit loop on EOF

sections = line.split('do()')
better = ''
for section in sections:
    print(section)
    better += 'X' + section.split('don\'t()')[0]
print(better)
matches = re.findall(exp, better)
total = sum((int(t[0]) * int(t[1]) for t in matches))
print(total)