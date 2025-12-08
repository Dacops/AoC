def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    spots = []
    for line in lines:
        x, y, z = map(int, line.strip().split(','))
        spots.append((x, y, z))

    from math import sqrt
    distances = [[0]*i for i in range(len(spots))]
    for i in range(len(spots)):
        for j in range(len(spots)):
            if i > j:
                x1, y1, z1 = spots[i]
                x2, y2, z2 = spots[j]
                distances[i][j] = sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)

    circuits = set()
    for i in range(len(spots)):
        circuits.add(frozenset({i}))

    NUM_PAIRS = 1000
    for _ in range(NUM_PAIRS):
        x, y = 0, 0
        min_dist = min(val for row in distances for val in row if val > 0)
        for i, row in enumerate(distances):
            if min_dist in row:
                x, y = row.index(min_dist), i
                break
        distances[y][x] = 0
        
        xset, yset = set(), set()
        for circuit in circuits:
            if x in circuit:
                xset = circuit
            if y in circuit:
                yset = circuit
        if xset != yset:
            circuits.remove(xset)
            circuits.remove(yset)
            circuits.add(xset.union(yset))

    from math import prod
    return prod(sorted((len(s) for s in circuits), reverse=True)[:3])

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    spots = []
    for line in lines:
        x, y, z = map(int, line.strip().split(','))
        spots.append((x, y, z))

    from math import sqrt
    distances = [[0]*i for i in range(len(spots))]
    for i in range(len(spots)):
        for j in range(len(spots)):
            if i > j:
                x1, y1, z1 = spots[i]
                x2, y2, z2 = spots[j]
                distances[i][j] = sqrt((x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2)

    circuits = set()
    for i in range(len(spots)):
        circuits.add(frozenset({i}))

    while True:
        x, y = 0, 0
        min_dist = min(val for row in distances for val in row if val > 0)
        for i, row in enumerate(distances):
            if min_dist in row:
                x, y = row.index(min_dist), i
                break
        distances[y][x] = 0
        
        xset, yset = set(), set()
        for circuit in circuits:
            if x in circuit:
                xset = circuit
            if y in circuit:
                yset = circuit
        if xset != yset:
            circuits.remove(xset)
            circuits.remove(yset)
            circuits.add(xset.union(yset))

        if len(circuits) == 1:
            return spots[x][0] * spots[y][0]

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")