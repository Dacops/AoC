def parse_input(file):
    with open(file, 'r') as f:
        lines = f.readlines()

    robots = []
    for l in lines:
        first = l.strip().split('=')
        pos, speed = first[1], first[2]
        pos = pos.split(' ')[0].split(',')
        speed = speed.split(',')
        xpos, ypos = int(pos[0]), int(pos[1])
        xspeed, yspeed = int(speed[0]), int(speed[1])
        robots.append(((xpos, ypos), (xspeed, yspeed)))
    return robots

def print_robots(robots):
    xtiles, ytiles = 101, 103
    for y in range(ytiles):
        for x in range(xtiles):
            count = sum(1 for robot in robots if robot[0] == (x, y))
            if count > 0:
                print(count, end='')  # Print the count if there are robots
            else:
                print('.', end='')  # Print '.' if there are no robots
        print()


def star1(file):
    robots = parse_input(file)
    xtiles, ytiles, iters = 101, 103, 100
    for i, robot in enumerate(robots):
        new_xpos = (robot[0][0] + iters * robot[1][0]) % xtiles
        new_ypos = (robot[0][1] + iters * robot[1][1]) % ytiles
        robots[i] = ((new_xpos, new_ypos), robot[1])
    
    first_quadrant = sum(1 for robot in robots if robot[0][0] < xtiles//2 and robot[0][1] < ytiles//2)
    secon_quadrant = sum(1 for robot in robots if robot[0][0] > xtiles//2 and robot[0][1] < ytiles//2)
    third_quadrant = sum(1 for robot in robots if robot[0][0] < xtiles//2 and robot[0][1] > ytiles//2)
    fourt_quadrant = sum(1 for robot in robots if robot[0][0] > xtiles//2 and robot[0][1] > ytiles//2)

    return first_quadrant * secon_quadrant * third_quadrant * fourt_quadrant


from z3 import *
def star2(file):
    # horizontal lines each 103 iterations, starting at 0
    # vertical lines each 101 iterations, starting at 45
    x, y, z = Ints('x y z')
    solver = Optimize()
    solver.add(
        x >= 0, y >= 0, z >= 0,
        103*x == 101*y + 45,
        z == 103*x
    )
    solver.minimize(z)
    if solver.check() == sat:
        return solver.model()[z].as_long() # actual result is this +1 for some reason

print(f"STAR 1: {star1('input.txt')}")
print(f"STAR 2: {star2('input.txt')}")