def recurs(past, vals, target, part2):
    new_past = []
    for p in past:
        if p > target:
            continue
        new_past.append(p * int(vals[0]))
        new_past.append(p + int(vals[0]))
        if part2:
            new_past.append(int(str(p) + vals[0]))
    
    if len(vals[1:]) == 0:
        return new_past
    
    return recurs(new_past, vals[1:], target, part2)


def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    eqs = []
    for l in lines:
        (val, vals) = l.strip().split(":")
        vals = vals.strip().split(" ")
        eqs.append((val, vals))

    correct = 0
    for (val, vals) in eqs:
        returns = recurs([int(vals[0])], vals[1:], int(val), False)
        if int(val) in returns:
            correct += int(val)

    return correct


def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    eqs = []
    for l in lines:
        (val, vals) = l.strip().split(":")
        vals = vals.strip().split(" ")
        eqs.append((val, vals))

    correct = 0
    for (val, vals) in eqs:
        returns = recurs([int(vals[0])], vals[1:], int(val), True)
        if int(val) in returns:
            correct += int(val)

    return correct


print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")