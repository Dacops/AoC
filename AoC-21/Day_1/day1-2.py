def counter(file):
    with open(file, 'r') as f:
        lst = f.readlines()

    count = 0
    for i in range(len(lst)-3):
        ant = int(lst[i])
        num = int(lst[i+3])
        if num > ant:
            count+=1
    return count