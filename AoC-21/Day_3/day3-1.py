def binary(file):
    with open(file, 'r') as f:
        lst = f.readlines()

    gamma, epsilon = '', ''
    for i in range(len(lst[0])-1):
        counter = {'0':0, '1':0}
        for line in lst:
            counter[line[i]]+=1
        if counter['0']>counter['1']:
            gamma,epsilon=gamma+'0',epsilon+'1'
        else:
            gamma,epsilon=gamma+'1',epsilon+'0'
    return int(gamma,2)*int(epsilon,2)