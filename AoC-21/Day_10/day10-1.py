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
        symbol = remover(line)
        if symbol!=None:
            symbols.append(symbol)
    
    score, total = {')':3, ']':57, '}':1197, '>':25137}, 0
    for element in symbols:
        total+=score[element]
    return total