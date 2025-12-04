def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    empty, rolls = set(), set()
    for y, line in enumerate(lines):
        for x, char in enumerate(line.strip()):
            if char == '@':
                rolls.add((y, x))
            if char == '.':
                empty.add((y, x))

    def num_adjacent(pos):
        y, x = pos
        neighbors = ((-1, -1), (-1, 0), (-1, 1), 
                     (0,  -1),          (0,  1), 
                     (1,  -1), (1,  0), (1,  1))
        return sum((y + dy, x + dx) in rolls for dy, dx in neighbors)

    return sum(num_adjacent(pos) < 4 for pos in rolls)

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    empty, rolls = set(), set()
    for y, line in enumerate(lines):
        for x, char in enumerate(line.strip()):
            if char == '@':
                rolls.add((y, x))
            if char == '.':
                empty.add((y, x))

    def num_adjacent(pos):
        y, x = pos
        neighbors = ((-1, -1), (-1, 0), (-1, 1), 
                     (0,  -1),          (0,  1), 
                     (1,  -1), (1,  0), (1,  1))
        return sum((y + dy, x + dx) in rolls for dy, dx in neighbors)

    og_count = 0
    while 1:
        count = 0
        remove = set()
        for pos in rolls:
            if num_adjacent(pos) < 4:
                remove.add(pos)
                count += 1
        if count == 0:
            break
        rolls -= remove
        og_count += count

    return og_count

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")