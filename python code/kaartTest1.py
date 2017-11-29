import math
import kaart

a = math.pi*.5


print(math.sin(a))

foo = kaart.Kaart()
for i in range(10):
    foo[i,6] = 1
for i in range(6):
    for j in range(10):
        foo[j,i] = 0
print(foo.how_far_line(6, 0, a))
foo[6,0]=0
print(foo)
for i in foo:
    print(i)