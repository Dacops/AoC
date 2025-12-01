def overlap(file):
    with open(file,'r') as f:
        lst=f.readlines()

    coordinates=[]
    for coordinate in lst:
        x1,y1=coordinate.split('->')[0].split(',')
        x2,y2=coordinate.split('->')[1].split(',')
        x1,y1,x2,y2=int(x1),int(y1),int(x2),int(y2)
        if x1==x2:
            for i in range(abs(y1-y2)+1):
                if y2>y1:
                    coordinates.append((x1,y1+i))
                if y1>y2:
                    coordinates.append((x1,y2+i))
        if y1==y2:
            for i in range(abs(x1-x2)+1):
                if x2>x1:
                    coordinates.append((x1+i,y1))
                if x1>x2:
                    coordinates.append((x2+i,y1))
        if abs(x1-x2)==abs(y1-y2):
            for i in range(abs(x1-x2)+1):
                if x2>x1 and y2>y1:
                    coordinates.append((x1+i,y1+i))
                if x2<x1 and y2>y1:
                    coordinates.append((x1-i,y1+i))
                if x2>x1 and y2<y1:
                    coordinates.append((x1+i,y1-i))
                if x2<x1 and y2<y1:
                    coordinates.append((x1-i,y1-i))
    
    all_coordinates={}
    for coordinate in coordinates:
        if coordinate not in all_coordinates:
            all_coordinates[coordinate]=0
        all_coordinates[coordinate]+=1
    counter=0
    for coordinate in all_coordinates:
        if all_coordinates[coordinate]>1:
            counter+=1
    return counter

print(overlap('C:\\Users\\david\\OneDrive\\Desktop\\GitHub\\AoC_21\\Day5\\day5_INPUT.txt'))