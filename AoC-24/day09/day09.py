def parse_input(file, star):
    with open(file, 'r') as f:
        lines = f.readlines()

    nums = ""
    for l in lines:
        nums += l.strip()

    files = []
    empty = []
    for i, n in enumerate(nums):
        empty.append(int(n)) if i%2 else files.append(int(n))

    if len(files) != len(empty):
        empty.append(0)

    output = []
    if star == 1:
        for i, (f, e) in enumerate(zip(files, empty)):
            for _ in range(f): output.append(str(i))
            for _ in range(e): output.append(".")

    if star == 2:
        for i, (f, e) in enumerate(zip(files, empty)):
            output.append([str(i), f])
            output.append([".", e])

    return output

def star1(file):
    output = parse_input(file, 1)
    
    i, j = 0, len(output)-1
    while i < j:
        if output[i] == ".":
            while output[j] == ".":
                if i >= j: break
                j -= 1
            temp = output[i]
            output[i] = output[j]
            output[j] = temp
        else:
            i += 1

    result = 0
    for i, n in enumerate(output):
        if n == ".":
            break
        result += i*int(n)

    return result

def star2(file):
    output = parse_input(file, 2)

    j = len(output)-1
    while j > 0:
        if output[j][0] != ".":
            i = 0
            while i < j:
                # simple swap
                if output[i][0] == "." and output[i][1] == output[j][1]:
                    output[i][0] = output[j][0]
                    output[j][0] = "."
                    break

                # not a complete swap
                elif output[i][0] == "." and output[i][1] > output[j][1]:
                    diff = output[i][1] - output[j][1]
                    output[i][0] = output[j][0]
                    output[j][0] = "."
                    output[i][1] = output[j][1]
                    output.insert(i+1, [".", diff])
                    break
                i += 1
        j -= 1  

    result, index = 0, 0
    for n in output:
        if n[0] == ".":
            index += int(n[1])
        else:
            for _ in range(n[1]):
                result += int(n[0])*index
                index += 1

    return result

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")