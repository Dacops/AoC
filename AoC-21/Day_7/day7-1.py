def fuel(file):
    with open(file,'r') as f:
        lst=str(f.readlines())[2:-2].split(',')

    lst=sorted(lst)
    ant=None
    for i in range(int(lst[0]),int(lst[-1])):
        total=0
        for element in lst:
            total+=abs(int(element)-int(i))
        if ant==None:
            ant=total
        else:
            if ant>total:
                ant=total
    return ant