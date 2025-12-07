def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    splitters, pos = set(), set()
    for y, line in enumerate(lines):
        for x, char in enumerate(line.strip()):
            if char == '^':
                splitters.add((y, x))
            elif char == 'S':
                pos.add((y, x))

    splits = 0
    for _ in range(len(lines)-1):
        new_pos = set()
        for y, x in pos:
            if (y+1, x) in splitters:
                splits += 1
                new_pos.add((y+1, x-1))
                new_pos.add((y+1, x+1))
            else:
                new_pos.add((y+1, x))
        pos = new_pos

    return splits

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    splitters, pos = set(), set()
    for y, line in enumerate(lines):
        for x, char in enumerate(line.strip()):
            if char == '^':
                splitters.add((y, x))
            elif char == 'S':
                pos.add((y, x))

    times = [0] * len(lines[-1])
    for i in range(len(lines)-1):
        new_pos = set()
        for y, x in pos:
            if (y+1, x) in splitters:
                new_pos.add((y+1, x-1))
                new_pos.add((y+1, x+1))
                times[x-1] += times[x]
                times[x+1] += times[x]
                times[x] = 0
            else:
                if sum(times) == 0:
                    times[x] += 1
                new_pos.add((y+1, x))
        pos = new_pos

    return sum(times)

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")