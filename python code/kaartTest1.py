import math
import kaart

a = math.pi*.5


print(math.sin(a))

foo = kaart.Kaart()
for i in range(10):
	foo.matrixRC[i][6] = 1
print(foo.how_far_line(6, 0, a))
foo.matrixRC[6][0]=0
print(foo)