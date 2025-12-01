def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    return [[x for x in l.strip()] for l in lines]

def explore(field, val, coords, visited, area, perimeter):
    new_vals = set()

    for coord in list(coords):
        if coord[0] > 0 and field[coord[0]-1][coord[1]] == val and (coord[0]-1, coord[1]) not in visited: 
            area += 1
            new_vals.add((coord[0]-1, coord[1]))
            visited.add((coord[0]-1, coord[1]))
        elif (coord[0]-1, coord[1]) not in visited:
            perimeter += 1

        if coord[0] < len(field)-1 and field[coord[0]+1][coord[1]] == val and (coord[0]+1, coord[1]) not in visited:
            area += 1
            new_vals.add((coord[0]+1, coord[1]))
            visited.add((coord[0]+1, coord[1]))
        elif (coord[0]+1, coord[1]) not in visited:
            perimeter += 1

        if coord[1] > 0 and field[coord[0]][coord[1]-1] == val and (coord[0], coord[1]-1) not in visited:
            area += 1
            new_vals.add((coord[0], coord[1]-1))
            visited.add((coord[0], coord[1]-1))
        elif (coord[0], coord[1]-1) not in visited:
            perimeter += 1

        if coord[1] < len(field[0])-1 and field[coord[0]][coord[1]+1] == val and (coord[0], coord[1]+1) not in visited:
            area += 1
            new_vals.add((coord[0], coord[1]+1))
            visited.add((coord[0], coord[1]+1))
        elif (coord[0], coord[1]+1) not in visited:
            perimeter += 1

    if len(new_vals) == 0:
        return area, perimeter, visited
    
    return explore(field, val, new_vals, visited, area, perimeter)
    

def star1(file):
    field = parse_input(file)
    
    vals = []
    y_max, x_max = len(field), len(field[0])

    done = set()
    for i in range(y_max):
        for j in range(x_max):
            if (i, j) not in done:
                current = set()
                current.add((i,j))
                area, perimeter, visited = explore(field, field[i][j], current, current, 1, 0)
                vals.append((area, perimeter))
                done = done.union(visited)
    
    return sum(area*perimeter for area, perimeter in vals)

def get_sides(field, coords):
    
    # check horizontal transitions
    right, cols, sides = False, set(), 0
    for i, row in enumerate(field):
        in_val = False
        for j, _ in enumerate(row):

            # transition, from val to not val or vice versa
            if ((i, j) in coords) ^ in_val:

                # if already in cols it's a side
                if (j, in_val) not in cols:
                    sides += 1

                cols.add((j, in_val))
                cols.discard((j, not in_val))
                in_val = not in_val

            else:
                # side ended
                cols.discard((j, in_val))
                cols.discard((j, not in_val))
    
        # transition to out of bounds
        if in_val:
            right = True

        elif right:
            sides += 1
            right = False
    
    if right:
        sides += 1

    # check vertical transitions
    down, rows = False, set()
    for i in range(len(field[0])):
        in_val = False
        for j in range(len(field)):

            # transition, from val to not val or vice versa
            if ((j, i) in coords) ^ in_val:

                # if already in cols it's a side
                if (j, in_val) not in rows:
                    sides += 1

                rows.add((j, in_val))
                rows.discard((j, not in_val))
                in_val = not in_val

            else:
                # side ended
                rows.discard((j, in_val))
                rows.discard((j, not in_val))
    
        # transition to out of bounds
        if in_val:
            down = True

        elif down:
            sides += 1
            down = False

    if down:
        sides += 1

    return sides


def star2(file):
    field = parse_input(file)
    
    vals = []
    y_max, x_max = len(field), len(field[0])

    done = set()
    for i in range(y_max):
        for j in range(x_max):
            if (i, j) not in done:
                current = set()
                current.add((i,j))
                area, _, visited = explore(field, field[i][j], current, current, 1, 0)
                sides = get_sides(field, visited)
                vals.append((area, sides))
                done = done.union(visited)

    return sum(area*sides for area, sides in vals)




print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")