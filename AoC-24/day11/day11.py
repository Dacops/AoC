def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    return [l for l in lines[0].split()]


def update_stones(stones):
    new_stones = []
    for s in stones:
        if s == '0':
            new_stones.append('1')
        elif len(s)&1:
            new_stones.append(str(int(s)*2024))
        else:
            new_stones.append(s[:len(s)//2])
            new_stones.append(str(int(s[len(s)//2:]))) # avoid '0...0' strings
    return new_stones

cache = {}

def update_stones_smart(stone, iters):
    global cache
    if iters in cache and stone in cache[iters]:
        return cache[iters][stone]
    if iters not in cache:
        cache[iters] = {}
    if iters == 0:
        return 1
    
    total = 0
    new_stones = update_stones([stone])
    for n in new_stones:
        total += update_stones_smart(n, iters-1)

    cache[iters][stone] = total
    return total

def star1(file):
    stones = parse_input(file)

    for _ in range(25):
        stones = update_stones(stones)

    return len(stones)


def star2(file):
    stones = parse_input(file)

    total = 0
    for s in stones:
        total += update_stones_smart(s, 75) # use dfs instead of bfs, so don't run out of memory

    return total



print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")