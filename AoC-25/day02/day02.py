def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    ranges = lines[0].split(',')
    total = 0
    for rng in ranges:
        start, end = map(int, rng.split('-'))
        lstr, lend = len(str(start)), len(str(end))

        for i in range(lstr,lend+1):
            if i%2==1: continue

            full = 10**(i-1)
            half = 10**(i//2-1)
            jump = half*10+1
            base = full+half
            if i == lstr: 
                base = start//(half*10)*jump
                if base < start: base += jump
            if i == lend: 
                while base <= end:
                    total += base
                    base += jump
            if i < lend:
                while base <= full*10:
                    total += base
                    base += jump
  
    return total

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    ranges = lines[0].split(',')
    total = 0
    for rng in ranges:
        start, end = map(int, rng.split('-'))

        for i in range(start,end+1):
            import re

            if re.fullmatch(r"(.+)\1+", str(i)):
                total += i
  
    return total

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")