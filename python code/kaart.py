# have not yet tested the changes to how_far_free and nearest_unknown

import math
Pi = math.pi


class Kaart:
    """ een matrix die de kaart van de auto aan gaat geven 0 is niets, 1 is iets
    en 2 is onbekend.
    !!!(2, 5) is de tweede rij en de vijfde colom!!!
    !!! colom telt van boven naar beneden, rij telt van links naar rechts!!!
    each pixel is one square cm
    """
    
    def __init__(self, rows = 10, colls = 10):
    	self.rows = rows
    	self.colls = colls
        self.matrixRC = []
        for _ in range(rows):
            self.matrixRC.append([2 for _ in range(colls)])


    def __str__(self):
        retVal = '\n'.join(''.join(map(str, row)) for row in self.matrixRC)
        for index, new in enumerate((' ', '#', '?')):
            retVal = retVal.replace(str(index), new)
        return retVal

            
    def _add(self, location = 0): #    0 = top; 1 = right; 2 = bot; 3 = left.
        if location == 0: #top
            for i in range(len(self.matrixRC)):
                self.matrixRC[i].insert(0, 2)
        elif location == 1: #right
            self.matrixRC.append([2 for _ in range( len( self.matrixRC(0) ) ) ])                      
        elif location == 2: #bottom
            for i in range(len(self.matrixRC)):
                self.matrixRC[i].append(2)
        elif location == 3: #left
            self.matrixRC.insert(0, [2 for _ in range( len( self.matrixRC(0) ) ) ] )
        else:
            raise Exception('Wrong value for _add function in matrix, expected location to be between 0 and 3 got', location)


    def _distance(self, x1, y1, x2, y2):
        return math.sqrt(math.pow((x1 - x2), 2) + math.pow((y1 - y2), 2))
        
    def _line_intersect_rect(self, x, y, angle, range): #returns all the values a line crosses.
    	a = math.cos(angle)
    	


    def how_high(self):
        return len(self.matrixRC[0])

    def how_wide(self):
        return len(self.matrixRC)


    def beam(self, x, y, angle, distance):
        pass

    

    def how_far_line(self, x, y, angle):
    	retVal = None
        a = math.tan(angle)
        ietsVakjes = [(X, Y) for X in range(self.rows) for Y in range(self.colls) if self.matrixRC[X][Y] == 1]
        print(ietsVakjes)
        for vakje in ietsVakjes:
            if(vakje[0]*a < vakje[1] and vakje[0]*a > vakje[1]-1) or ((vakje[0]+1)*a < vakje[1] and (vakje[0]+1)*a > vakje[1]-1) or (vakje[0]*a < vakje[1] and (vakje[0]+1)*a > vakje[1]-1) or (vakje[0]*a > vakje[1] and (vakje[0]+1)*a < vakje[1]-1): # seeing if my imaginairy line crosses the square
            	print(vakje)
            	if retVal != None: retVal = min(retVal, self._distance(x, y, vakje[0], vakje[1]))
            	else: retVal = self._distance(x, y, vakje[0], vakje[1])
        return retVal

        
        
        
    def how_far_free(self, x, y, angle, breedte):
        retVal = None
        for i in range(breedte+1):
        	newX = math.sin(angle) * (i   -.5 * breedte) + x
        	newY = math.cos(angle) * (i   -.5 * breedte) + y
    		foo = self.how_far_line(newX, newY, angle)
    		if retVal == None or foo < retVal:
    			retVal = foo
    	return retVal


    def nearest_unknown(self, x, y):
    	retVal = None
        unknownLocations = [(X, Y) for X in range(self.rows) for Y in range(self.colls) if self.matrixRC[X][Y] == 2]
        for loc in unknownLocations:
        	foo = self._distance(foo[0], foo[1], x, y)
			if retVal == None or foo < retVal:
				retVal = foo
		return retVal
		

    def combine(self, other, locationDefinement):
        pass

