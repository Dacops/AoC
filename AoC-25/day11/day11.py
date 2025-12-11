def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    paths = {}
    for line in lines:
        inn, out = line.strip().split(':')
        inn = inn.split()[0]

        paths[inn] = set()
        for outs in out.split():
            paths[inn].add(outs)
    
    def flood(curr):
        total = 0
        nextt = paths[curr]
        for n in nextt:
            if n == 'out':
                return 1
            curr = n
            total += flood(curr)
        return total                

    return flood('you')

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    paths = {}
    for line in lines:
        inn, out = line.strip().split(':')
        inn = inn.split()[0]

        paths[inn] = set()
        for outs in out.split():
            paths[inn].add(outs)

    cache = {}
    def flood(curr, target):
        if (curr,target) in cache:
            return cache[(curr,target)]
        
        if target != 'out' and curr == 'out':
            return 0

        total, og_curr = 0, curr
        nextt = paths[curr]
        for n in nextt:
            if n == target:
                return 1
            curr = n
            total += flood(curr,target)
        cache[(og_curr,target)] = total
        return total                

    return flood('svr', 'fft') * flood('fft', 'dac') * flood('dac', 'out')

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")