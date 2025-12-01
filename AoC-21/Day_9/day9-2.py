from functools import reduce

def baisin(file):
    with open(file,'r') as f:
        lst=f.readlines()

    floor = []
    for l in lst:
        if l[-1] not in '0123456789':
            l=l[:-1]
        floor.append(list(map(lambda x:x!='9', l)))
    
    y, coords = 0, []
    for line in floor:
        x=0
        for value in line:
            if value:
                coords.append((x,y))
            x+=1
        y+=1

    basins=[]
    for y in range(len(floor)):
        for x in range(len(floor[y])):
            if (x, y) in coords:
                basin,ant=[(x, y)],[[]]
                del coords[coords.index((x, y))]
                while ant!=basin:
                    ant=basin
                    for element in basin:
                        if (element[0]-1, element[1]) in coords:
                            basin.append((element[0]-1, element[1]))
                            del coords[coords.index((element[0]-1, element[1]))]
                        if (element[0]+1, element[1]) in coords:
                            basin.append((element[0]+1, element[1]))
                            del coords[coords.index((element[0]+1, element[1]))]
                        if (element[0], element[1]-1) in coords:
                            basin.append((element[0], element[1]-1))
                            del coords[coords.index((element[0], element[1]-1))]
                        if (element[0], element[1]+1) in coords:
                            basin.append((element[0], element[1]+1))
                            del coords[coords.index((element[0], element[1]+1))]
                if basin!=[]:
                    basins.append(basin)

    
    bigger=[]
    size = list(map(lambda x:len(x), basins))
    for i in range(3):
        bigger.append(max(size))
        del size[size.index(max(size))]

    return reduce(lambda x,y:x*y, bigger)