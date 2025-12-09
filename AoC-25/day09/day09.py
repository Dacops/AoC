def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    coords = []
    for line in lines:
        x, y = map(int, line.strip().split(','))
        coords.append((x, y))

    max_dist = 0
    for x1, y1 in coords:
        for x2, y2 in coords:
            if x1 < x2 and y1 < y2:
                max_dist = max(max_dist, (abs(x1 - x2)+1) * (abs(y1 - y2)+1))

    return max_dist

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    coords = []
    max_x, max_y = 0, 0
    for line in lines:
        x, y = map(int, line.strip().split(','))
        max_x = max(x, max_x)
        max_y = max(y, max_y)
        coords.append((x, y))

    edges = []
    for i, (x1, y1) in enumerate(coords):
        if i == len(coords) - 1:
            x2, y2 = coords[0]
        else:
            x2, y2 = coords[i+1]
            edges += [(x1, y1)]

        if x1 == x2:
            tmin_y = min(y1, y2)
            for i in range(abs(y1 - y2) - 1):
                edges += [(x1, tmin_y+i+1)]

        elif y1 == y2:
            tmin_x = min(x1, x2)
            for i in range(abs(x1 - x2) - 1):
                edges += [(tmin_x+i+1, y1)]

    sort_edges_x = [[] for _ in range(max_x+1)]
    sort_edges_y = [[] for _ in range(max_y+1)]
    for x, y in edges:
        sort_edges_x[x] += [(x,y)]
        sort_edges_y[y] += [(x,y)]

    for arr in sort_edges_x:
        arr.sort()
    for arr in sort_edges_y:
        arr.sort(key=lambda t: (t[1], t[0]))

    outside = set()
    for col in sort_edges_x:
        iin = False
        prev = -1
        for i, (x, y) in enumerate(col):
            if not iin:
                outside.add((x,y-1))
                iin = True

            elif abs(prev - y) != 1 and i+1 != len(col) and abs(col[i+1][1]-y) != 1:
                outside.add((x, y+1))
                iin = False
            
            elif i+1 == len(col):
                outside.add((x, y+1))
            prev = y

    for row in sort_edges_y:
        iin = False
        prev = -1
        for i, (x, y) in enumerate(row):
            if not iin:
                outside.add((x-1,y))
                iin = True

            elif abs(prev - x) != 1 and i+1 != len(row) and abs(row[i+1][1]-x) != 1:
                outside.add((x+1, y))
                iin = False

            elif i+1 == len(row):
                outside.add((x+1, y))
            prev = x

    rectangles = []
    for x1, y1 in coords:
        for x2, y2 in coords:
            if x1 < x2 and y1 < y2:
                area = (abs(x1 - x2)+1) * (abs(y1 - y2)+1)
                rectangles += [(area, (x1,y1), (x2,y2))]
    rectangles.sort(reverse=True)

    for area, (x1,y1), (x2,y2) in rectangles:
        if (x1, y1) != (x2, y2):
            xmin, xmax = sorted([x1, x2])
            ymin, ymax = sorted([y1, y2])

            end = 0
            for x in range(xmin, xmax + 1):
                if (x, y1) in outside or (x, y2) in outside:
                    end = 1
                    break
            if end: continue

            for y in range(ymin, ymax + 1):   
                if (x1, y) in outside or (x2, y) in outside:
                    end = 1
                    break
            if end: continue

            return area

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")