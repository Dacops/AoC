def fuel(file):
    with open(file,'r') as f:
        lst=str(f.readlines())[2:-2].split(',')

    total=0
    for number in lst:
        total+=int(number)
    avg=(int(total/len(lst)))

    def fac(mov):
        total=0
        while mov!=0:
            total+=mov
            mov-=1
        return total

    total=0
    for element in lst:
        mov=abs(int(element)-avg)
        total+=fac(mov)
    return total