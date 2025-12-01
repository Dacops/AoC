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
        global last_x
        global last_y
        for i in range(len(coordinates)):
            if mode=='x':
                last_x = value
                x, y = coordinates[i].split(',')
                x, y, value = int(x), int(y), int(value)
                if x>value: coordinates[i] = '{},{}'.format(2*value-x, y)
            if mode=='y':
                last_y = value
                x, y = coordinates[i].split(',')
                x, y, value = int(x), int(y), int(value)
                if y>value: coordinates[i] = '{},{}'.format(x, 2*value-y)

    for instruction in instructions:
        mode, value = instruction.split('=')
        bend(coordinates, mode, value)
    
    new_coordinates=[]
    for coordinate in coordinates:
        if coordinate not in new_coordinates: new_coordinates.append(coordinate)

    final=''
    for y in range(last_y):
        line=''
        for x in range(last_x):
            if '{},{}'.format(x,y) in new_coordinates: line+='#'
            else: line+='.'
        final+=line+'\n'
    return final