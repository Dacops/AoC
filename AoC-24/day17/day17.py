def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    regA, regB, regC, pgrm = 0, 0, 0, []
    for line in lines:
        line = line.strip().split(':')
        
        if line[0] == 'Register A':
            regA = int(line[1].strip())
        if line[0] == 'Register B':
            regB = int(line[1].strip())
        if line[0] == 'Register C':
            regC = int(line[1].strip())
        if line[0] == 'Program':
            pgrm = [l for l in line[1].strip().split(',')]

    return regA, regB, regC, pgrm

def execute(pgrm, regA, regB, regC):
    i, output = 0, []

    while i < len(pgrm):
        if pgrm[i] == '0': # adv, combo
            if int(pgrm[i+1]) <= 3:
                regA = regA // 2**int(pgrm[i+1])
            elif int(pgrm[i+1]) == 4:
                regA = regA // 2**regA
            elif int(pgrm[i+1]) == 5:
                regA = regA // 2**regB
            elif int(pgrm[i+1]) == 6:
                regA = regA // 2**regC
            i += 2
        
        elif pgrm[i] == '1': # bxl, literal
            regB = regB ^ int(pgrm[i+1])
            i += 2

        elif pgrm[i] == '2': # bst, combo
            if int(pgrm[i+1]) <= 3:
                regB = int(pgrm[i+1]) % 8
            elif int(pgrm[i+1]) == 4:
                regB = regA % 8
            elif int(pgrm[i+1]) == 5:
                regB = regB % 8
            elif int(pgrm[i+1]) == 6:
                regB = regC % 8
            elif int(pgrm[i+1]) == 7:
                regB = 7
            i += 2

        elif pgrm[i] == '3': # jnz, literal
            if regA != 0:
                i = int(pgrm[i+1])
            else:
                i += 2
        
        elif pgrm[i] == '4': # bxc, ignore
            regB = regB ^ regC
            i += 2

        elif pgrm[i] == '5': # out, combo
            if int(pgrm[i+1]) <= 3:
                output.append(int(pgrm[i+1]) % 8)
            elif int(pgrm[i+1]) == 4:
                output.append(regA % 8)
            elif int(pgrm[i+1]) == 5:
                output.append(regB % 8)
            elif int(pgrm[i+1]) == 6:
                output.append(regC % 8)
            elif int(pgrm[i+1]) == 7:
                output.append(7)
            i += 2
        
        elif pgrm[i] == '6': # ~adv, combo
            if int(pgrm[i+1]) <= 3:
                regB = regA // 2**int(pgrm[i+1])
            elif int(pgrm[i+1]) == 4:
                regB = regA // 2**regA
            elif int(pgrm[i+1]) == 5:
                regB = regA // 2**regB
            elif int(pgrm[i+1]) == 6:
                regB = regA // 2**regC
            elif int(pgrm[i+1]) == 7:
                regB = regA // 2**7
            i += 2

        elif pgrm[i] == '7':    # ~adv, combo
            if int(pgrm[i+1]) <= 3:
                regC = regA // 2**int(pgrm[i+1])
            elif int(pgrm[i+1]) == 4:
                regC = regA // 2**regA
            elif int(pgrm[i+1]) == 5:
                regC = regA // 2**regB
            elif int(pgrm[i+1]) == 6:
                regC = regA // 2**regC
            elif int(pgrm[i+1]) == 7:
                regC = regA // 2**7
            i += 2

    return ",".join(map(str, output))

def ddexecute(pgrm, regA, regB, regC, lvl=0):
    for _ in range(8):
        if execute(pgrm, regA, regB, regC) == ",".join(map(str, pgrm[-(lvl+1):])):
            if lvl+1 == len(pgrm):
                return regA
            res = ddexecute(pgrm, regA*8, regB, regC, lvl+1)
            if res: return res
        regA += 1

def star1(file):
    regA, regB, regC, pgrm = parse_input(file)
    return execute(pgrm, regA, regB, regC)

def star2(file):
    _, regB, regC, pgrm = parse_input(file)
    return ddexecute("".join(map(str, pgrm)), 0, regB, regC)

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")