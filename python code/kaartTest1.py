import math
import kaart

foo = kaart.Kaart()
for i in range(10):
    foo[6,i] = 1
for i in range(10):
    for j in range(6):
        foo[j, i] = 0
print(foo.how_far_line(0, 7, .5*math.pi))