import sys
import os
import aocd

cmd = sys.argv[1]
day = int(sys.argv[2])
folder = f"day {day}"
if cmd == "make":
    os.mkdir(folder)
    data = aocd.get_data(day=day, year = 2024)
    os.chdir(folder)
    with open('input.txt', 'x') as f:
        f.write(data)
    os.popen("cp ../template.c ./main.c")
elif cmd == "run":
    os.chdir(folder)
    os.system(f"gcc ./main.c -o main.exe; ./main.exe")

