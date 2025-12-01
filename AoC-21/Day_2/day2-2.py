def position(file):
    with open(file, 'r') as f:
        lst = f.readlines()

    v_mov, h_mov, aim = 0, 0, 0
    for line in lst:
        mov, val = line.split()
        val=int(val)
        if mov=='up':
            aim-=val
        if mov=='down':
            aim+=val
        if mov=='forward':
            h_mov+=val
            v_mov+=aim*val
    return h_mov*v_mov