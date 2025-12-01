def position(file):
    with open(file, 'r') as f:
        lst = f.readlines()

    v_mov, h_mov = 0, 0
    for line in lst:
        mov, val = line.split()
        val=int(val)
        if mov=='up':
            v_mov-=val
        if mov=='down':
            v_mov+=val
        if mov=='forward':
            h_mov+=val
    return h_mov*v_mov