def counter(file):
    with open(file, 'r') as f:
        lst = f.readlines()

    ant, count = None, 0
    for num in lst:
        num = int(num)
        if ant != None:
            if num > ant:
                count+=1
        ant = num
    return count