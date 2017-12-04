for _ in range(10):
	matrixRC.append([2 for _ in range(10)])

retVal = '\n'.join(''.join(map(str, row)) for row in matrixRC)
	for index, new in enumerate((' ', '#', '?')):
		retVal = retVal.replace(str(index), new)
	print(retVal)
	print("")

matrixRC[1][1] = 1

retVal = '\n'.join(''.join(map(str, row)) for row in matrixRC)
    for index, new in enumerate((' ', '#', '?')):
        retVal = retVal.replace(str(index), new)
	print(retVal)
	print("")


matrixRC[4, 4] = 1
	

retVal = '\n'.join(''.join(map(str, row)) for row in matrixRC)
    for index, new in enumerate((' ', '#', '?')):
        retVal = retVal.replace(str(index), new)
	print(retVal)
	print("")