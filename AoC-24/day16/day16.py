def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    maze = []
    for i, l in enumerate(lines):
        maze.append(list(l.strip()))
        if 'S' in l:
            init_pos = (i, l.index('S'))
        if 'E' in l:
            end_pos = (i, l.index('E'))

    return maze, init_pos, end_pos, "east"

def bfs(maze, end_pos, queue):
    cache = {}
    while queue:
        score, pos, direction = queue.pop()

        if (pos, direction) in cache and cache[(pos, direction)] <= score:
            continue
        reach_values = [cache[(end_pos, direction)] for direction in ["east", "west", "north", "south"] if (end_pos, direction) in cache]
        if end_pos in cache and min(reach_values) <= score:
            continue
        cache[(pos, direction)] = score

        if pos == end_pos:
            continue

        y, x = pos
        if direction == "east":
            if maze[y][x+1] != "#":
                queue.append((score+1, (y, x+1), "east"))
            if maze[y+1][x] != "#":
                queue.append((score+1000, (y, x), "south"))
            if maze[y-1][x] != "#":
                queue.append((score+1000, (y, x), "north"))
    
        elif direction == "west":
            if maze[y][x-1] != "#":
                queue.append((score+1, (y, x-1), "west"))
            if maze[y+1][x] != "#":
                queue.append((score+1000, (y, x), "south"))
            if maze[y-1][x] != "#":
                queue.append((score+1000, (y, x), "north"))

        elif direction == "north":
            if maze[y-1][x] != "#":
                queue.append((score+1, (y-1, x), "north"))
            if maze[y][x+1] != "#":
                queue.append((score+1000, (y, x), "east"))
            if maze[y][x-1] != "#":
                queue.append((score+1000, (y, x), "west"))

        elif direction == "south":
            if maze[y+1][x] != "#":
                queue.append((score+1, (y+1, x), "south"))
            if maze[y][x+1] != "#":
                queue.append((score+1000, (y, x), "east"))
            if maze[y][x-1] != "#":
                queue.append((score+1000, (y, x), "west"))

        if (y,x) == (6,5):
            print(score, direction)

    return cache

def star1(file):
    maze, init_pos, end_pos, direction = parse_input(file)
    cache = bfs(maze, end_pos, [(0, init_pos, direction)])
    reach_values = [cache[(end_pos, direction)] for direction in ["east", "west", "north", "south"] if (end_pos, direction) in cache]
    return min(reach_values)

def star2(file):
    maze, init_pos, end_pos, direction = parse_input(file)
    cache = bfs(maze, end_pos, [(0, init_pos, direction)])
    reach_values = [cache[(end_pos, direction)] for direction in ["east", "west", "north", "south"] if (end_pos, direction) in cache]
    max_path = min(reach_values)

    # pre-process cache to remove redundant paths
    for i, row in enumerate(maze):
        for j, _ in enumerate(row):
            if ((i, j), "east") in cache and ((i, j), "west") in cache and ((i, j-1), "east") in cache and ((i, j+1), "west") in cache:
                if cache[((i, j-1), "east")] < cache[((i, j+1), "west")]:
                    del cache[((i, j+1), "west")]
                elif cache[((i, j-1), "east")] > cache[((i, j+1), "west")]:
                    del cache[((i, j-1), "east")]
            if ((i, j), "north") in cache and ((i, j), "south") in cache and ((i-1, j), "south") in cache and ((i+1, j), "north") in cache:
                if cache[((i-1, j), "south")] < cache[((i+1, j), "north")]:
                    del cache[((i+1, j), "north")]
                elif cache[((i-1, j), "south")] > cache[((i+1, j), "north")]:
                    del cache[((i-1, j), "south")]

    backtrack, visited = [(end_pos, max_path)], set()
    while backtrack:
        (y, x), max_path = backtrack.pop()
        visited.add((y, x))

        if (y, x) == init_pos:
            continue

        for dy, dx in [(0, 1), (1, 0), (0, -1), (-1, 0)]:
            if dy == 1 and ((y+dy,x+dx), "north") in cache and cache[((y+dy, x+dx), "north")] < max_path:
                backtrack.append(((y+dy, x+dx), cache[((y+dy, x+dx), "north")]))
            if dy == -1 and ((y+dy,x+dx), "south") in cache and cache[((y+dy, x+dx), "south")] < max_path:
                backtrack.append(((y+dy, x+dx), cache[((y+dy, x+dx), "south")]))
            if dx == 1 and ((y+dy,x+dx), "west") in cache and cache[((y+dy, x+dx), "west")] < max_path:
                backtrack.append(((y+dy, x+dx), cache[((y+dy, x+dx), "west")]))
            if dx == -1 and ((y+dy,x+dx), "east") in cache and cache[((y+dy, x+dx), "east")] < max_path:
                backtrack.append(((y+dy, x+dx), cache[((y+dy, x+dx), "east")]))

    return len(visited)


print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")