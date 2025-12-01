def parse_input1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    world, directions, starting_pos, counter, mode = [], [], 0, 0, 0
    for l in lines:
        if l=="\n":
            mode = 1
            continue
        if not mode:
            row = list(l.strip())
            if '@' in row:
                starting_pos = (counter, row.index('@'))
            world.append(row)
            counter += 1
        else:
            for d in l.strip():
                directions.append(d)
    return world, directions, starting_pos

def parse_input2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    world, directions, starting_pos, counter, mode = [], [], 0, 0, 0
    for l in lines:
        if l=="\n":
            mode = 1
            continue
        if not mode:
            row = []
            for r in l.strip():
                if r == '#':
                    row.append('#')
                    row.append('#')
                if r == '.':
                    row.append('.')
                    row.append('.')
                if r == 'O':
                    row.append('[')
                    row.append(']')
                if r == '@':
                    row.append('@')
                    row.append('.')
                    starting_pos = (counter, row.index('@'))
            world.append(row)
            counter += 1
        else:
            for d in l.strip():
                directions.append(d)
    return world, directions, starting_pos

def print_world(world):
    for row in world:
        for x in row:
            print(x, end='')
        print()

def star1(file):
    world, directions, pos = parse_input1(file)

    for d in directions:
        if d == '^':
            if world[pos[0]-1][pos[1]] == '#':  # wall can't move
                continue
            if world[pos[0]-1][pos[1]] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]-1][pos[1]] = '@'
                pos = (pos[0]-1, pos[1])
                continue
            if world[pos[0]-1][pos[1]] == 'O':  # box, check if can move
                temp_pos = (pos[0]-1, pos[1])
                while world[temp_pos[0]-1][temp_pos[1]] != '#':
                    if world[temp_pos[0]-1][temp_pos[1]] == '.':    # push all boxes
                        world[temp_pos[0]-1][temp_pos[1]] = 'O'     # just add one to this spot
                        world[pos[0]-1][pos[1]] = '@'               # and move the @
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0]-1, pos[1])
                        break
                    temp_pos = (temp_pos[0]-1, temp_pos[1])
        if d == 'v':
            if world[pos[0]+1][pos[1]] == '#':  # wall can't move
                continue
            if world[pos[0]+1][pos[1]] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]+1][pos[1]] = '@'
                pos = (pos[0]+1, pos[1])
                continue
            if world[pos[0]+1][pos[1]] == 'O':  # box, check if can move
                temp_pos = (pos[0]+1, pos[1])
                while world[temp_pos[0]+1][temp_pos[1]] != '#':
                    if world[temp_pos[0]+1][temp_pos[1]] == '.':    # push all boxes
                        world[temp_pos[0]+1][temp_pos[1]] = 'O'     # just add one to this spot
                        world[pos[0]+1][pos[1]] = '@'               # and move the @
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0]+1, pos[1])
                        break
                    temp_pos = (temp_pos[0]+1, temp_pos[1])
        if d == '<':
            if world[pos[0]][pos[1]-1] == '#':  # wall can't move
                continue
            if world[pos[0]][pos[1]-1] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]][pos[1]-1] = '@'
                pos = (pos[0], pos[1]-1)
                continue
            if world[pos[0]][pos[1]-1] == 'O':  # box, check if can move
                temp_pos = (pos[0], pos[1]-1)
                while world[temp_pos[0]][temp_pos[1]-1] != '#':
                    if world[temp_pos[0]][temp_pos[1]-1] == '.':    # push all boxes
                        world[temp_pos[0]][temp_pos[1]-1] = 'O'     # just add one to this spot
                        world[pos[0]][pos[1]-1] = '@'               # and move the @
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0], pos[1]-1)
                        break
                    temp_pos = (temp_pos[0], temp_pos[1]-1)
        if d == '>':
            if world[pos[0]][pos[1]+1] == '#':  # wall can't move
                continue
            if world[pos[0]][pos[1]+1] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]][pos[1]+1] = '@'
                pos = (pos[0], pos[1]+1)
                continue
            if world[pos[0]][pos[1]+1] == 'O':  # box, check if can move
                temp_pos = (pos[0], pos[1]+1)
                while world[temp_pos[0]][temp_pos[1]+1] != '#':
                    if world[temp_pos[0]][temp_pos[1]+1] == '.':    # push all boxes
                        world[temp_pos[0]][temp_pos[1]+1] = 'O'     # just add one to this spot
                        world[pos[0]][pos[1]+1] = '@'               # and move the @
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0], pos[1]+1)
                        break
                    temp_pos = (temp_pos[0], temp_pos[1]+1)

    gps = 0
    for i, row in enumerate(world):
        for j, x in enumerate(row):
            if x == 'O':
                gps += i*100 + j

    return gps

def star2(file):
    world, directions, pos = parse_input2(file)

    for d in directions:
        if d == '^':
            if world[pos[0]-1][pos[1]] == '#':  # wall can't move
                continue
            if world[pos[0]-1][pos[1]] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]-1][pos[1]] = '@'
                pos = (pos[0]-1, pos[1])
                continue
            if world[pos[0]-1][pos[1]] in ['[', ']']:  # box, check if can move
                prev_pos = []
                temp_pos = [(pos[0]-1, pos[1])]
                if world[pos[0]-1][pos[1]] == '[': temp_pos.append((pos[0]-1, pos[1]+1))
                if world[pos[0]-1][pos[1]] == ']': temp_pos.append((pos[0]-1, pos[1]-1))
                prev_pos.append(temp_pos)
                while all(world[p[0]-1][p[1]] != '#' for p in prev_pos[-1]):
                    if all(world[p[0]-1][p[1]] == '.' for p in prev_pos[-1]):    # push all boxes
                        while prev_pos:
                            for p in prev_pos[-1]:
                                world[p[0]-1][p[1]] = world[p[0]][p[1]]
                                world[p[0]][p[1]] = '.'
                            prev_pos.pop()
                        world[pos[0]-1][pos[1]] = '@'
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0]-1, pos[1])
                        break
                    new_pos = set()
                    for p in prev_pos[-1]:
                        if world[p[0]-1][p[1]] == '[':
                            new_pos.add((p[0]-1, p[1]))
                            new_pos.add((p[0]-1, p[1]+1))
                        if world[p[0]-1][p[1]] == ']':
                            new_pos.add((p[0]-1, p[1]))
                            new_pos.add((p[0]-1, p[1]-1))
                    prev_pos.append(list(new_pos))
        if d == 'v':
            if world[pos[0]+1][pos[1]] == '#':  # wall can't move
                continue
            if world[pos[0]+1][pos[1]] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]+1][pos[1]] = '@'
                pos = (pos[0]+1, pos[1])
                continue
            if world[pos[0]+1][pos[1]] in ['[', ']']:  # box, check if can move
                prev_pos = []
                temp_pos = [(pos[0]+1, pos[1])]
                if world[pos[0]+1][pos[1]] == '[': temp_pos.append((pos[0]+1, pos[1]+1))
                if world[pos[0]+1][pos[1]] == ']': temp_pos.append((pos[0]+1, pos[1]-1))
                prev_pos.append(temp_pos)
                while all(world[p[0]+1][p[1]] != '#' for p in prev_pos[-1]):
                    if all(world[p[0]+1][p[1]] == '.' for p in prev_pos[-1]):    # push all boxes
                        while prev_pos:
                            for p in prev_pos[-1]:
                                world[p[0]+1][p[1]] = world[p[0]][p[1]]
                                world[p[0]][p[1]] = '.'
                            prev_pos.pop()
                        world[pos[0]+1][pos[1]] = '@'
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0]+1, pos[1])
                        break
                    new_pos = set()
                    for p in prev_pos[-1]:
                        if world[p[0]+1][p[1]] == '[':
                            new_pos.add((p[0]+1, p[1]))
                            new_pos.add((p[0]+1, p[1]+1))
                        if world[p[0]+1][p[1]] == ']':
                            new_pos.add((p[0]+1, p[1]))
                            new_pos.add((p[0]+1, p[1]-1))
                    prev_pos.append(list(new_pos))
        if d == '<':
            if world[pos[0]][pos[1]-1] == '#':  # wall can't move
                continue
            if world[pos[0]][pos[1]-1] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]][pos[1]-1] = '@'
                pos = (pos[0], pos[1]-1)
                continue
            if world[pos[0]][pos[1]-1] == ']':  # box, check if can move
                temp_pos = (pos[0], pos[1]-1)
                while world[temp_pos[0]][temp_pos[1]-1] != '#':
                    if world[temp_pos[0]][temp_pos[1]-1] == '.':    # push all boxes
                        world[temp_pos[0]][temp_pos[1]-1] = '['
                        right = 1
                        while temp_pos != (pos[0], pos[1]-1):
                            if right:
                                world[temp_pos[0]][temp_pos[1]] = ']'
                                right = 0
                            else:
                                world[temp_pos[0]][temp_pos[1]] = '['
                                right = 1
                            temp_pos = (temp_pos[0], temp_pos[1]+1)
                        world[pos[0]][pos[1]-1] = '@'
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0], pos[1]-1)
                        break
                    temp_pos = (temp_pos[0], temp_pos[1]-1)
        if d == '>':
            if world[pos[0]][pos[1]+1] == '#':  # wall can't move
                continue
            if world[pos[0]][pos[1]+1] == '.':  # empty, regular move
                world[pos[0]][pos[1]] = '.'
                world[pos[0]][pos[1]+1] = '@'
                pos = (pos[0], pos[1]+1)
                continue
            if world[pos[0]][pos[1]+1] == '[':  # box, check if can move
                temp_pos = (pos[0], pos[1]+1)
                while world[temp_pos[0]][temp_pos[1]+1] != '#':
                    if world[temp_pos[0]][temp_pos[1]+1] == '.':    # push all boxes
                        world[temp_pos[0]][temp_pos[1]+1] = ']'
                        right = 1
                        while temp_pos != (pos[0], pos[1]+1):
                            if right:
                                world[temp_pos[0]][temp_pos[1]] = '['
                                right = 0
                            else:
                                world[temp_pos[0]][temp_pos[1]] = ']'
                                right = 1
                            temp_pos = (temp_pos[0], temp_pos[1]-1)
                        world[pos[0]][pos[1]+1] = '@'
                        world[pos[0]][pos[1]] = '.'
                        pos = (pos[0], pos[1]+1)
                        break
                    temp_pos = (temp_pos[0], temp_pos[1]+1)

    gps = 0
    for i, row in enumerate(world):
        for j, x in enumerate(row):
            if x == '[':
                gps += i*100 + j

    return gps

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")