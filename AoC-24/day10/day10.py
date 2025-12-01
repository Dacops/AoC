def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    topo_map = []
    for l in lines:
        topo_map.append(l.strip())

    zeroes = []
    for i, row in enumerate(lines):
        for j, r in enumerate(row):
            if r == '0':
                zeroes.append((i,j))

    return topo_map, zeroes

def recurs(topo_map, currs, lvl):
    new_currs = []
    y_max, x_max = len(topo_map), len(topo_map[0])
    for i, j in currs:
        if i > 0 and int(topo_map[i-1][j]) == lvl+1:
            new_currs.append((i-1, j))
        if i < y_max-1 and int(topo_map[i+1][j]) == lvl+1:
            new_currs.append((i+1, j))
        if j > 0 and int(topo_map[i][j-1]) == lvl+1:
            new_currs.append((i, j-1))
        if j < x_max-1 and int(topo_map[i][j+1]) == lvl+1:
            new_currs.append((i, j+1))

    if lvl + 1 == 9:
        return new_currs
    return recurs(topo_map, new_currs, lvl+1)


def star1(file):
    topo_map, zeroes = parse_input(file)
    paths = 0
    for zero in zeroes:
        paths += len(set(recurs(topo_map, [zero], 0)))
    return paths


def star2(file):
    topo_map, zeroes = parse_input(file)
    paths = 0
    for zero in zeroes:
        paths += len(recurs(topo_map, [zero], 0))
    return paths


print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")