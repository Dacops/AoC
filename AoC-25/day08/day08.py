def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    spots = []
    for line in lines:
        x, y, z = map(int, line.strip().split(','))
        spots.append((x, y, z))

    from math import sqrt
    distances = []
    for i in range(len(spots)):
        for j in range(len(spots)):
            if i > j:
                x1, y1, z1 = spots[i]
                x2, y2, z2 = spots[j]
                dist = sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)
                distances += [(dist, i, j)]
    distances = sorted(distances)

    def boss(x):
        while parent[x] != x:
            x = parent[x]
        return x

    NUM_PAIRS = 1000
    parent = [i for i in range(len(spots))]
    for _ in range(NUM_PAIRS):
        _, x, y = distances.pop(0)
        parent[boss(x)] = boss(y)

    def kids(sons, count):
        new_sons = []
        for i in range(len(parent)):
            if parent[i] in sons and i not in sons:
                new_sons += [i]
                count += 1
        if new_sons:
            return kids(new_sons, count)
        return count

    sizes = [-1 for _ in range(len(spots))]
    for i in range(len(parent)):
        if parent[i] == i:
            sizes[i] = kids([i], 1)

    sizes = sorted(sizes, reverse=True)
    return sizes[0] * sizes[1] * sizes[2]

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    spots = []
    for line in lines:
        x, y, z = map(int, line.strip().split(','))
        spots.append((x, y, z))

    from math import sqrt
    distances = []
    for i in range(len(spots)):
        for j in range(len(spots)):
            if i > j:
                x1, y1, z1 = spots[i]
                x2, y2, z2 = spots[j]
                dist = sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)
                distances += [(dist, i, j)]
    distances = sorted(distances)

    def boss(x):
        while parent[x] != x:
            x = parent[x]
        return x

    parent = [i for i in range(len(spots))]
    while True:
        dist, x, y = distances.pop(0)
        parent[boss(x)] = boss(y)

        if sum(parent[i] == i for i in range(len(parent))) == 1:
            return spots[x][0] * spots[y][0]

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")