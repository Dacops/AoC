def star1(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    nums, signs = [], []
    for i, line in enumerate(lines):
        line = line.strip()

        if i == len(lines) - 1:
            for char in line.split():
                signs.append(char)
            break

        lnums = []
        for num in line.split():
            lnums.append(int(num))
        nums.append(lnums)

    total = 0
    for i, sign in enumerate(signs):
        if sign == '+':
            total += sum(num[i] for num in nums)
        elif sign == '*':
            from math import prod
            total += prod(num[i] for num in nums)

    return total

def star2(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    whole = []
    for line in lines:
        line = line.rstrip('\n')

        temp = []
        for char in line:
            temp.append(char)
        whole.append(temp)

    nums, total = [], 0
    for i in range(len(whole[0])):
        if whole[-1][i] != ' ':
            sign = whole[-1][i]
        
        num = 0
        for j in range(len(whole)-1):
            if whole[j][i] != ' ':
                num = num * 10 + int(whole[j][i])
        if num != 0: nums.append(num)

        if all(col[i] == ' ' for col in whole) or i == len(whole[0]) - 1:
            if sign == '+':
                total += sum(num for num in nums)
            elif sign == '*':
                from math import prod
                total += prod(num for num in nums)
            nums = []

    return total

    return 0

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")