def lanternfish(file):
    with open(file,'r') as f:
        lst=str(f.readlines())[2:-2].split(',')
        
    elements={'0':0,'1':0,'2':0,'3':0,'4':0,'5':0,'6':0,'7':0,'8':0}
    for element in lst:
        elements[element]+=1
    for i in range(80):
        born=elements['0']
        elements['0']=elements['1']
        elements['1']=elements['2']
        elements['2']=elements['3']
        elements['3']=elements['4']
        elements['4']=elements['5']
        elements['5']=elements['6']
        elements['6']=elements['7']+born
        elements['7']=elements['8']
        elements['8']=born

    return (elements['0']+
            elements['1']+
            elements['2']+
            elements['3']+
            elements['4']+
            elements['5']+
            elements['6']+
            elements['7']+
            elements['8'])