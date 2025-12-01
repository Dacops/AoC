def path(file):
    with open(file,'r') as f:
        lst=f.readlines()
    
    for l in lst:
        if l[-1]=='\n':
            lst[lst.index(l)]=l[:-1]

    d, small_caves = {}, []
    for l in lst:
        f, s = l.split('-')[0], l.split('-')[1]
        if f in d and s!='start': d[f] += ',{}'.format(s)
        if s in d and f!='start': d[s] += ',{}'.format(f)
        if f not in d and s!='start': d[f] = s
        if s not in d and f!='start': d[s] = f
        if f.islower() and len(f)==1 and f not in small_caves: small_caves.append(f)
        if s.islower() and len(s)==1 and s not in small_caves: small_caves.append(s)
    
    past_caves={}
    for cave in d:
        past_caves[cave]=0
    
    def path_finder(position, past_caves, small_visited):
        if position=='end': return 1
        if past_caves[position]>0 and position.islower() and small_visited: return 0
        if position in past_caves and position.islower(): 
            past_caves[position]+=1
            if past_caves[position]==2: small_visited=True
        path_count=0
        for path in d[position].split(','):
            path_count += path_finder(path, past_caves, small_visited)
        past_caves[position]-=1
        return path_count

    return path_finder('start', past_caves, False)