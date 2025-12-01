def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    result, count = 50, 0
    for instr in lines:
        side, val = instr[0], int(instr[1:])
        if side == 'L':
            result = (result - val) % 100
        if side == 'R':
            result = (result + val) % 100
        
        if result == 0:
            count += 1

    return count

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    result, count = 50, 0
    for instr in lines:
        side, val = instr[0], int(instr[1:])
        if side == 'L':
            if result == 0:
                count -= 1
            if (result - val) <= 0:
                count += abs(result - val) // 100 + 1
            result = (result - val) % 100
        if side == 'R':
            if (result + val) >= 100:
                count += abs(result + val) // 100
            result = (result + val) % 100

    return count

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")