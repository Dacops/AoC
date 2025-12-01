def digits(file):
    with open(file,'r') as f:
        lst=f.readlines()

    total=0
    for line in lst:
        control_sequence, sequence = (str(line).split(' | '))
        control_sequence, sequence = control_sequence.split(' '), sequence.split(' ')
        sequence[-1]=sequence[-1][:-1]

        important_digits = []
        for digit in control_sequence:
            if (len(digit)==2 or
                len(digit)==3 or
                len(digit)==4 or
                len(digit)==7):
                important_digits.append(sorted(digit))
        
        for digit in sequence:
            digit = sorted(digit)
            for element in important_digits:
                if element==digit:
                    print(digit)
                    total+=1

    return total