def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    patterns, available_patterns = lines[0].strip().split(','), {}
    patterns = [p.strip() for p in patterns]
    min_lenght = min([len(p) for p in patterns])
    max_lenght = max([len(p) for p in patterns])

    for pattern in patterns:
        available_patterns[pattern] = 1

    desired_patterns = []
    for pattern in lines[2:]:
        desired_patterns.append(pattern.strip())

    return available_patterns, min_lenght, max_lenght, desired_patterns

def recurs(available_patterns, impossible_patterns, min_length, max_length, pattern):
    if pattern in available_patterns.keys():
        return available_patterns[pattern]
    elif pattern in impossible_patterns:
        return 0
    total = 0
    for i in range(min_length, max_length+1):
        if pattern[:i] in available_patterns.keys():
            print(pattern[:i], pattern[i:])
            total += recurs(available_patterns, impossible_patterns, min_length, max_length, pattern[i:])
    if total:
        available_patterns[pattern] = total
    else:
        impossible_patterns.add(pattern)
    return total

def star1(file):
    available_patterns, min_length, max_length, desired_patterns = parse_input(file)
    return sum((recurs(available_patterns, set(), min_length, max_length, pattern) and 1) for pattern in desired_patterns)

def star2(file):
    available_patterns, min_length, max_length, desired_patterns = parse_input(file)
    
    # check if given towels can be built with others
    ap, apkeys = available_patterns.copy(), sorted(available_patterns.keys(), key=len)
    for pattern in apkeys:
        if len(pattern) == 1:
            continue
        del ap[pattern]
        val = recurs(ap, set(), min_length, max_length, pattern)
        if val:
            ap[pattern] += val
        else:
            ap[pattern] = available_patterns[pattern]
    
    for pattern in desired_patterns:
        print(" -> ", pattern, recurs(ap, set(), min_length, max_length, pattern))
    return sum(recurs(ap, set(), min_length, max_length, pattern) for pattern in desired_patterns)	

    # brgr shows 3 instead of 2
    # b + rgr
    # rgr gets splitted twice, into r + gr and rg + r
    # even though rg is r + g (cached from bwurrg)
    # dups 1 

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")