def octopus(file):
    with open(file,'r') as f:
        lst=f.readlines()
    for line in lst:
        if line[-1] not in '0123456789':
            lst[lst.index(line)]=line[:-1]

    coords, count = {}, 0
    for y in range(len(lst)):
        for x in range(len(lst[y])):
            coords['({}, {})'.format(x,y)]=int(lst[y][x])

    for i in range(100):

        for y in range(len(lst)):
            for x in range(len(lst[y])):
                coords['({}, {})'.format(x,y)]+=1

        while True:
            for coord in coords:
                if coords[coord]>9:

                    up_left = str((int(coord[1:-1].split(',')[0])-1, int(coord[1:-1].split(',')[1])-1))
                    up = str((int(coord[1:-1].split(',')[0]), int(coord[1:-1].split(',')[1])-1))
                    up_right = str((int(coord[1:-1].split(',')[0])+1, int(coord[1:-1].split(',')[1])-1))
                    left = str((int(coord[1:-1].split(',')[0])-1, int(coord[1:-1].split(',')[1])))
                    current = str((int(coord[1:-1].split(',')[0]), int(coord[1:-1].split(',')[1])))
                    right = str((int(coord[1:-1].split(',')[0])+1, int(coord[1:-1].split(',')[1])))
                    down_left = str((int(coord[1:-1].split(',')[0])-1, int(coord[1:-1].split(',')[1])+1))
                    down = str((int(coord[1:-1].split(',')[0]), int(coord[1:-1].split(',')[1])+1))
                    down_right = str((int(coord[1:-1].split(',')[0])+1, int(coord[1:-1].split(',')[1])+1))
            
                    if up_left in coords and coords[up_left]!=0: coords[up_left]+=1
                    if up in coords and coords[up]!=0: coords[up]+=1
                    if up_right in coords and coords[up_right]!=0: coords[up_right]+=1
                    if left in coords and coords[left]!=0: coords[left]+=1
                    if right in coords and coords[right]!=0: coords[right]+=1
                    if down_left in coords and coords[down_left]!=0: coords[down_left]+=1
                    if down in coords and coords[down]!=0: coords[down]+=1
                    if down_right in coords and coords[down_right]!=0: coords[down_right]+=1

                    coords[current]=0
                    count+=1

            any=0
            for coord in coords:
                if coords[coord]>9:
                    any+=1

            if any==0:
                break

    return count