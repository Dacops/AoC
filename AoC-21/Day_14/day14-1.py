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

    def grow_polymer(polymer, count):
        ant, inside = None, []
        for letter in polymer:
            if ant!=None:
                if ant+letter in polymers:
                    ins = enter[polymers.index(ant+letter)]
                    inside.append(ins)
            ant=letter
    
        new_polymer=polymer[0]
        for i in range(len(inside)):
            new_polymer+=inside[i]+polymer[i+1]
        
        count+=1
        if count<10: return grow_polymer(new_polymer, count)
        else:
            d={}
            for letter in new_polymer:
                if letter not in d: d[letter]=0
                if letter in d: d[letter]+=1
            values=[]
            for element in d:
                values.append(d[element])
            values = sorted(values)
            return values[-1]-values[0]

    return grow_polymer(polymer, 0)