def transform(file):
    with open(file,'r') as f:
        lst=f.readlines()

    coordinates, instructions = [], []
    for l in lst:
        l = l.rstrip()
        if len(l.split(' '))==1 and l!='':
            coordinates.append(l)
        if len(l.split(' '))>1 and l!='':
            instructions.append(l[11:])

    def bend(coordinates, mode, value):
        for i in range(len(coordinates)):
            if mode=='x':
                x, y = coordinates[i].split(',')
                x, y, value = int(x), int(y), int(value)
                if x>value: coordinates[i] = '{},{}'.format(2*value-x, y)
            if mode=='y':
                x, y = coordinates[i].split(',')
                x, y, value = int(x), int(y), int(value)
                if y>value: coordinates[i] = '{},{}'.format(x, 2*value-y)

    for instruction in instructions:
        mode, value = instruction.split('=')
        bend(coordinates, mode, value)
        new_coordinates=[]
        for coordinate in coordinates:
            if coordinate not in new_coordinates: new_coordinates.append(coordinate)
        return len(new_coordinates)