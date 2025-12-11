def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    targets, buttons = [], [[] for _ in range(len(lines))]
    for j, line in enumerate(lines):
        for i, l in enumerate(line.split()):

            if 0 < i < len(line.split())-1:
                buttons[j] += [tuple(map(int, l.strip("()").split(",")))]

            elif not i:
                lt, target = 0, 0
                for c in l.strip('[]'):
                    lt += 1
                    target <<= 1
                    if c == '#':
                        target |= 1
                targets += [(lt-1, target)]

            else:
                continue #only use in 2.
    
    def bfs(curr, idx, rounds):
        new_vals = set()
        for c in curr:
            for button in buttons[idx]:
                val = c
                for b in button:
                    val ^= 1 << targets[idx][0] - int(b)
                if val == targets[idx][1]:
                    return rounds
                new_vals.add(val)
        return bfs(new_vals, idx, rounds+1)

    return sum(bfs([0],i,1) for i in range(len(targets)))

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    targets, buttons = [[] for _ in range(len(lines))], [[] for _ in range(len(lines))]
    for j, line in enumerate(lines):
        for i, l in enumerate(line.split()):

            if 0 < i < len(line.split())-1:
                buttons[j] += [tuple(map(int, l.strip("()").split(",")))]

            elif not i:
                continue #only use in 1

            else:
                targets[j] = tuple(map(int, l.strip("{}").split(",")))
    
    total = 0
    for idx in range(len(targets)):
        n_buttons = len(buttons[idx])
        n_counters = len(targets[idx])
        presses = [Int(f"press_{i}") for i in range(n_buttons)]
        constraints = [p >= 0 for p in presses]

        final_vals = []
        for j in range(n_counters):
            val = Sum([If(j in buttons[idx][b], presses[b], 0) for b in range(n_buttons)])
            final_vals.append(val)

        constraints += [final_vals[j] == targets[idx][j] for j in range(n_counters)]
        s = Optimize()
        s.add(constraints)
        s.minimize(Sum(presses))

        if s.check() == sat:
            m = s.model()
            rounds_needed = sum([m[p].as_long() for p in presses])
            total += rounds_needed

    return total

from z3 import *
print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")