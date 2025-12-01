def function(file):
    with open(file,'r') as f:
        lst=f.readlines()
    polymer=lst[0].rstrip()
    instructions=[]
    for instruction in lst[1:]:
        if instruction != '\n': instructions.append(instruction.rstrip())
    polymers, enter = [], []
    for instruction in instructions:
        pol, ent = instruction.split(' -> ')
        polymers.append(pol)
        enter.append(ent)
    
    ant, poly = None, {}
    for letter in polymer:
        if ant!=None:
            if ant+letter not in poly: poly[ant+letter]=0
            if ant+letter in poly: poly[ant+letter]+=1
        ant=letter

    def grow_polymer(poly, count):
        poly_c = {}
        for group in poly:
            first_half, second_half = group[0]+enter[polymers.index(group)], enter[polymers.index(group)]+group[1]
            if first_half not in poly_c: poly_c[first_half]=0
            if first_half in poly_c: poly_c[first_half]+=poly[group]
            if second_half not in poly_c: poly_c[second_half]=0
            if second_half in poly_c: poly_c[second_half]+=poly[group]
        count+=1
        if count<40: return grow_polymer(poly_c, count)
        else:
            values={}
            for key in poly_c:
                if key[0] not in values: values[key[0]]=0
                if key[0] in values: values[key[0]]+=poly_c[key]
                if key[1] not in values: values[key[1]]=0
                if key[1] in values: values[key[1]]+=poly_c[key]
            new_values = []
            for value in values:
                new_values.append(values[value]/2)
            new_values = sorted(new_values)
            return round(new_values[-1]-new_values[0])

    return grow_polymer(poly, 0)