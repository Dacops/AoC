def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    nodes = []
    for l in lines:
        nodes.append(l.strip())

    max_y = len(nodes)
    max_x = len(nodes[0])

    antenas = {}
    for i in range(max_y):
        for j in range(max_x):
            if nodes[i][j] == ".":
                continue
            if nodes[i][j] in antenas:
                antenas[nodes[i][j]].append((i,j))
            else:
                antenas[nodes[i][j]] = [(i,j)]

    return nodes, antenas, max_x, max_y

def star1(file):
    nodes, antenas, max_x, max_y = parse_input(file)

    antinodes = set()
    for antena in antenas:
        coords = antenas[antena]
        for i in range(len(coords)):
            for j in range(i+1, len(coords)):
                y_diff = abs(coords[i][0] - coords[j][0])
                x_diff = abs(coords[i][1] - coords[j][1])

                # coords[i] is guaranteed to be above coords[j]
                # unknonw if to the left or right
                # coords[i] top left, coords[j] bottom right
                if coords[i][1] < coords[j][1]:
                    if coords[i][1] - x_diff >= 0 and coords[i][0] - y_diff >= 0:
                        antinodes.add((coords[i][0] - y_diff, coords[i][1] - x_diff))

                    if coords[j][1] + x_diff < max_x and coords[j][0] + y_diff < max_y:
                        antinodes.add((coords[j][0] + y_diff, coords[j][1] + x_diff))

                # coords[i] top right, coords[j] bottom left
                else:
                    if coords[i][1] + x_diff < max_x and coords[i][0] - y_diff >= 0:
                        antinodes.add((coords[i][0] - y_diff, coords[i][1] + x_diff))

                    if coords[j][1] - x_diff >= 0 and coords[j][0] + y_diff < max_y:
                        antinodes.add((coords[j][0] + y_diff, coords[j][1] - x_diff))

    return len(antinodes)


# not a single diff, propagate diffs until out of bounds
def star2(file):
    nodes, antenas, max_x, max_y = parse_input(file)

    antinodes = set()
    for antena in antenas:
        coords = antenas[antena]
        for i in range(len(coords)):
            for j in range(i+1, len(coords)):
                y_diff = abs(coords[i][0] - coords[j][0])
                x_diff = abs(coords[i][1] - coords[j][1])

                # antenas now are also antinodes
                antinodes.add(coords[i])
                antinodes.add(coords[j])

                # coords[i] is guaranteed to be above coords[j]
                # unknonw if to the left or right
                # coords[i] top left, coords[j] bottom right
                if coords[i][1] < coords[j][1]:
                    tx_diff, ty_diff = x_diff, y_diff
                    while (coords[i][1] - tx_diff >= 0 and coords[i][0] - ty_diff >= 0):
                        antinodes.add((coords[i][0] - ty_diff, coords[i][1] - tx_diff))
                        tx_diff += x_diff
                        ty_diff += y_diff

                    tx_diff, ty_diff = x_diff, y_diff
                    while (coords[j][1] + tx_diff < max_x and coords[j][0] + ty_diff < max_y):
                        antinodes.add((coords[j][0] + ty_diff, coords[j][1] + tx_diff))
                        tx_diff += x_diff
                        ty_diff += y_diff

                # coords[i] top right, coords[j] bottom left
                else:
                    tx_diff, ty_diff = x_diff, y_diff
                    while (coords[i][1] + tx_diff < max_x and coords[i][0] - ty_diff >= 0):
                        antinodes.add((coords[i][0] - ty_diff, coords[i][1] + tx_diff))
                        tx_diff += x_diff
                        ty_diff += y_diff

                    tx_diff, ty_diff = x_diff, y_diff
                    while (coords[j][1] - tx_diff >= 0 and coords[j][0] + ty_diff < max_y):
                        antinodes.add((coords[j][0] + ty_diff, coords[j][1] - tx_diff))
                        tx_diff += x_diff
                        ty_diff += y_diff
    
    return len(antinodes)


print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")