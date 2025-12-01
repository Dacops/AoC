def digits(file):
    with open(file,'r') as f:
        lst=f.readlines()

    final=[]
    for line in lst:
        control_sequence, sequence = (str(line).split(' | '))
        control_sequence, sequence = control_sequence.split(' '), sequence.split(' ')
        if sequence[-1][-1] not in 'abcdefg':
            sequence[-1]=sequence[-1][:-1]

        for digit in control_sequence:
            if (len(digit)==2):
                two=sorted(digit)
            if (len(digit)==3):
                three=sorted(digit)
            if (len(digit)==4):
                four=sorted(digit)
            if (len(digit)==7):
                seven=sorted(digit)
        
        f=[]
        for digit in sequence:

            if len(digit)==2:
                f.append(1)
            elif len(digit)==3:
                f.append(7)
            elif len(digit)==4:
                f.append(4)
            elif len(digit)==7:
                f.append(8)

            else:
                if len(digit)==5:
                    count1, count2 = 0, 0

                    for num in two:
                        if num in sorted(digit):
                            count1+=1
                    
                    eight_four=[]
                    for num in seven:
                        if num not in four:
                            eight_four.append(num)

                    for num in eight_four:
                        if num in sorted(digit):
                            count2+=1

                    if count1==2:
                        f.append(3)
                    elif count2==3:
                        f.append(2)
                    else:
                        f.append(5)

                    
                if len(digit)==6:
                    count1, count2 = 0, 0

                    for num in two:
                        if num not in sorted(digit):
                            count1+=1

                    eight_three=[]
                    for num in seven:
                        if num not in four:
                            eight_three.append(num)

                    for num in eight_three:
                        if num not in sorted(digit):
                            count2+=1

                    if count1>0:
                        f.append(6)
                    elif count2>0:
                        f.append(9)
                    else:
                        f.append(0)
            
        final.append(f)

    total=0
    for seq in final:
        val = (seq[0]*1000+
               seq[1]*100+
               seq[2]*10+
               seq[3]*1)
        total+=val
        print(val)
    return total