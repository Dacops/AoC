def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    ranges, ingrs = [], []
    ninput = 0
    for line in lines:
        line = line.strip()
        if line == '':
            ninput += 1
            continue

        if not ninput:
            begin, end = line.split('-')
            ranges.append((int(begin), int(end)))
        if ninput:
            ingrs.append(int(line))

    count = 0
    for ingr in ingrs:
        for begin, end in ranges:
            if begin <= ingr <= end:
                count += 1
                break

    return count

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    ranges = []
    for line in lines:
        line = line.strip()
        if line == '':
            break

        begin, end = line.split('-')
        ranges.append((int(begin), int(end)))

    def compact_ranges(ranges):
        compact = [ranges[0]]
        for rng in ranges[1:]:
            hit = 0
            for r in compact:
                if rng[0] <= r[0] <= rng[1]:
                    nr = (rng[0], max(rng[1], r[1]))
                    compact.remove(r)
                    compact += [nr]
                    hit += 1
                    break
                if r[0] <= rng[0] <= r[1]:
                    nr = (r[0], max(rng[1], r[1]))
                    compact.remove(r)
                    compact += [nr]
                    hit += 1
                    break
            if not hit: compact += [rng]
        return compact

    old_len, new_len = len(ranges), 0
    while old_len != new_len:
        ranges = compact_ranges(ranges)
        old_len, new_len = new_len, len(ranges)

    count = 0
    for begin, end in ranges:
        count += end - begin + 1

    return count

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")