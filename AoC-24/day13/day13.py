def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    entries, entry = [], []
    for i, l in enumerate(lines):
        if i%4==0 or i%4==1:
            splits = l.strip().split('+')
            entry.append((splits[1].split(',')[0], splits[2]))
        if i%4==2:
            splits = l.strip().split('=')
            entry.append((splits[1].split(',')[0], splits[2]))
        if i%4==3:
            entries.append(entry)
            entry = []
    entries.append(entry)
    entry = []

    return entries


from z3 import *
def get_total(entries):
    results = []
    for entry in entries: 
        ax, ay, bx, by = Ints('ax ay bx by')
        solver = Optimize()
        solver.add(
            ax >= 0, ay >= 0, bx >= 0, by >= 0,
            ax == ay, bx == by,
            ax * int(entry[0][0]) + bx * int(entry[1][0]) == int(entry[2][0]),
            ay * int(entry[0][1]) + by * int(entry[1][1]) == int(entry[2][1])
        )
        solver.minimize(3*ax + bx)
        if solver.check() == sat:
            results.append(solver.model())

    total = 0
    for result in results:
        total += 3*result[ax].as_long() + result[bx].as_long()

    return total

def star1(file):
    entries = parse_input(file)
    return get_total(entries)

def star2(file):
    entries = parse_input(file)
    for i in range(len(entries)):
        entries[i][2] = (str(int(entries[i][2][0]) + int(10e12)), str(int(entries[i][2][1]) + int(10e12)))
    return get_total(entries)
    





print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")