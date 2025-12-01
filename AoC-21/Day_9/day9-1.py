def baisin(file):
    with open(file,'r') as f:
        lst=f.readlines()

    values = []
    for l in lst:
        curr = lst.index(l)
        if l[-1] not in '0123456789':
            l=l[:-1]
        for i in range(len(l)):
            ant, next = 10, 10
            if i>0:
                ant=int(l[i-1])
            if i<len(l)-1:
                next=int(l[i+1])
            if int(l[i])<ant and int(l[i])<next:
                bef, aft = 10, 10
                if curr>0:
                    bef=int(lst[curr-1][i])
                if curr<len(lst)-1:
                    aft=int(lst[curr+1][i])
                if int(l[i])<bef and int(l[i])<aft:
                    values.append(int(l[i]))
    return sum(list(map(lambda x:x+1, values)))