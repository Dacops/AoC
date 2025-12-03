def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    total = 0
    for line in lines:
        line = list(map(int, line.strip()))
        frst = line.index(max(line))
        if frst == len(line)-1:
            total += max(line[:-1])*10 + max(line)
            continue
        total += max(line)*10 + max(line[frst+1:])

    return total

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    def max_n_left(line, left):
        frst, val = line.index(max(line)), max(line)
        while len(line) - frst < left:
            frst, val = line.index(max(line[:frst])), max(line[:frst])
        return val, line[frst+1:]

    total = 0
    JOLTAGE_LEN = 12
    for line in lines:
        line = list(map(int, line.strip()))
        ttotal = 0
        for i in range(JOLTAGE_LEN):
            val, line = max_n_left(line, JOLTAGE_LEN-i)
            ttotal = ttotal * 10 + val
        total += ttotal

    return total

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")