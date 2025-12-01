def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    xmin, ymin, xmax, ymax, init = 0, 0, 70, 70, 1024
    start_pos, end_pos = (xmin, ymin), (xmax, ymax)
    init_coords, remainder = set(), []
    
    for i, l in enumerate(lines):
        if i >= init: remainder.append(tuple(map(int, l.strip().split(','))))
        else: init_coords.add(tuple(map(int, l.strip().split(','))))

    return init_coords, remainder, xmin, ymin, xmax, ymax, start_pos, end_pos

def bfs_fill(coords, cache, queue, xmin, ymin, xmax, ymax):
    new_queue = []
    while queue:
        pos = queue.pop()
        for dx, dy in [(1,0), (-1,0), (0,1), (0,-1)]:
            adj_pos = (pos[0]+dx, pos[1]+dy)
            if adj_pos[0] < xmin or adj_pos[0] > xmax or adj_pos[1] < ymin or adj_pos[1] > ymax or adj_pos in coords:
                continue
            if adj_pos not in cache:
                cache[adj_pos] = cache[pos] + 1
                new_queue.append(adj_pos)
            elif cache[adj_pos] > cache[pos] + 1:
                cache[adj_pos] = cache[pos] + 1
                new_queue.append(adj_pos)
    if new_queue:
        return bfs_fill(coords, cache, new_queue, xmin, ymin, xmax, ymax)
    return cache

def bfs_reach(coords, cache, queue, xmin, ymin, xmax, ymax):
    if (xmax, ymax) in cache:
        return cache
    new_queue = []
    while queue:
        pos = queue.pop()
        for dx, dy in [(1,0), (-1,0), (0,1), (0,-1)]:
            adj_pos = (pos[0]+dx, pos[1]+dy)
            if adj_pos[0] < xmin or adj_pos[0] > xmax or adj_pos[1] < ymin or adj_pos[1] > ymax or adj_pos in coords:
                continue
            if adj_pos not in cache:
                cache[adj_pos] = cache[pos] + 1
                new_queue.append(adj_pos)
            elif cache[adj_pos] > cache[pos] + 1:
                cache[adj_pos] = cache[pos] + 1
                new_queue.append(adj_pos)
    if new_queue:
        return bfs_fill(coords, cache, new_queue, xmin, ymin, xmax, ymax)
    return cache

def star1(file):
    coords, _, xmin, ymin, xmax, ymax, start_pos, end_pos = parse_input(file)
    cache = bfs_fill(coords, {start_pos:0}, [start_pos], xmin, ymin, xmax, ymax)
    return cache[end_pos]

def star2(file):
    import sys
    sys.setrecursionlimit(10000)
    
    coords, remainder, xmin, ymin, xmax, ymax, start_pos, end_pos = parse_input(file)
    while remainder:
        next_obs = remainder.pop(0)
        coords.add(next_obs)
        cache = bfs_fill(coords, {start_pos:0}, [start_pos], xmin, ymin, xmax, ymax)
        
        if end_pos not in cache.keys():
            return str(next_obs[0]) + ',' + str(next_obs[1])


print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")