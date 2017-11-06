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
            if(vakje[0]*a < vakje[1] and vakje[0]*a > vakje[1]-1) or ((vakje[0]+1)*a < vakje[1] and (vakje[0]+1)*a > vakje[1]-1) or (vakje[0]*a < vakje[1] and (vakje[0]+1)*a > vakje[1]-1) or (vakje[0]*a > vakje[1] and (vakje[0]+1)*a < vakje[1]-1):
            	print(vakje)
            	if retVal != None: retVal = min(retVal, self._distance(x, y, vakje[0], vakje[1]))
            	else: retVal = self._distance(x, y, vakje[0], vakje[1])
        return retVal

        
        
        
    def how_far_free(self, x, y, angle):
        pass

    def nearest_unknown(self, x, y):
        unknownLocations = [(X, Y) for X in range(3) for Y in range(3) if self.matrixRC[X][Y] == 2]
        


    def combine(self, other, locationDefinement):
        pass

