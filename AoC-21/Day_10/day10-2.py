def subsystem(file):
    with open(file,'r') as f:
        lst = f.readlines()

    symbols, rs = [], {'{':'}', '[':']', '(':')', '<':'>', '}':'nop', ']':'nop', ')':'nop', '>':'nop'}
    for line in lst:
        def remover(line):
            ant, count, c = None, 0, line
            for element in line:
                if ant!=None:
                    if rs[ant]==element:
                        line = line[:count-1] + line[count+1:]
                        return remover(line)
                ant, count = element, count+1
            if c==line:
                for element in line:
                    if element in '>}])':
                        return element
        symbols.append(remover(line))
    
    incomplete=[]
    for i in range(len(symbols)):
        if symbols[i]==None:
            incomplete.append(lst[i])
    
    lack=[]
    for line in incomplete:
        def remover(line):
            ant, count, c = None, 0, line
            for element in line:
                if ant!=None:
                    if rs[ant]==element:
                        line = line[:count-1] + line[count+1:]
                        return remover(line)
                ant, count = element, count+1
            if c==line:
                return line
        lack.append(remover(line))
    
    results=[]
    for line in lack:
        if line[-1] not in '<({[':
            line=line[:-1]
        l=''
        for element in line[::-1]:
            l+=str(rs[element])
        results.append(l)
    
    values, val = {')':1, ']':2, '}':3, '>':4}, []
    for line in results:
        v=0
        for element in line:
            v*=5
            v+=values[element]
        val.append(v)
    val = sorted(val)

    return val[int(len(val)/2)]