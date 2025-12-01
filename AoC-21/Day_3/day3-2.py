def life_support(file):
    with open(file, 'r') as f:
        lst = f.readlines()

    def oxygen(lst):
        for i in range(len(lst[0])-1):
            counter = {'0':0, '1':0}
            for line in lst:
                counter[line[i]]+=1
            if counter['0']>counter['1']:
                lst=list(filter(lambda x: x[i]=='0', lst))
            if counter['0']<counter['1']:
                lst=list(filter(lambda x: x[i]=='1', lst))
            if counter['0']==counter['1']:
                lst=list(filter(lambda x: x[i]=='1', lst))
            if len(lst)==1:
                return int(lst[0],2)

    def CO2(lst):
        for i in range(len(lst[0])-1):
            counter = {'0':0, '1':0}
            for line in lst:
                counter[line[i]]+=1
            if counter['0']>counter['1']:
                lst=list(filter(lambda x: x[i]=='1', lst))
            if counter['0']<counter['1']:
                lst=list(filter(lambda x: x[i]=='0', lst))
            if counter['0']==counter['1']:
                lst=list(filter(lambda x: x[i]=='0', lst))
            if len(lst)==1:
                return int(lst[0],2)

    return oxygen(lst)*CO2(lst)