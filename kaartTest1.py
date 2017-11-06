import math
import kaart

print(math.tan(math.pi*.5))

foo = kaart.Kaart()
for i in range(10):
	print(i)
	foo.matrixRC[i][6] = 1
print(foo.how_far_line(6, 0, math.pi*.25))
foo.matrixRC[6][0]=0
print(foo)