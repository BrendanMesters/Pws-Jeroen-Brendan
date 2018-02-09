# have not yet tested the changes to how_far_free and nearest_unknown



import math
Pi = math.pi


class Kaart:
    """ een matrix die de kaart van de auto aan gaat geven 0 is niets, 1 is iets
    en 2 is onbekend.
    links boven is (0,0) als je x naar rechts gaat en y naar beneden ben je bij locatie (x,y)
    !!! colom telt van boven naar beneden, rij telt van links naar rechts!!!
    each pixel is one square cm
    de locatie van het middenpunt van elk vakje word dus in halven, 
    het midden van het linker boven vakje is dan dus (0.5, 0.5)
    """
    
    def __init__(self, rowsLen = 10, collsLen = 11, file='test123.txt'): #werkt
        self.matrixRC = []
        if not file:
            self.rowsLen = rowsLen
            self.collsLen = collsLen
            for _ in range(rowsLen):
                self.matrixRC.append([2 for _ in range(collsLen)])
        else:
            pre_map = open(file)
            pre_lines = pre_map.readlines()
            lines = list(map(lambda l:l.strip('\n'), pre_lines))
            self.rowsLen = len(lines)
            self.collsLen = max(map(len, lines))
            for line in lines:
                    self.matrixRC.append(list(line))
            print(self.rowsLen, self.collsLen)
                



    def __str__(self): #werkt
#        retVal = '\n'.join(''.join(map(str, row)) for row in self.matrixRC) #Werkte niet zoals ik wilde
        retVal = str()
        for i in range(len(self.matrixRC)):
            retVal += '\n'
            for j in range(len(self.matrixRC[i])):
                retVal += str(self[i,j])
        for index, new in enumerate((' ', '#', '?')):
            retVal = retVal.replace(str(index), new)
        return retVal


    def __getitem__(self, key): #werkt
        r, c = key
        return self.matrixRC[r][c]


    def __setitem__(self, key, value): #werkt
        r, c = key
        self.matrixRC[r][c] = value


    def __iter__(self): #werkt
        for i in self.matrixRC:
            for j in i:
                yield j


    def __next__(self): #werkt
        for i in self.matrixRC:
            for j in i:
                return j



    def _add(self, location = 0): #    0 = top; 1 = right; 2 = bot; 3 = left. #werkt
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


    def _distance(self, x1, y1, x2, y2): #werkt
        return math.sqrt(math.pow((x1 - x2), 2) + math.pow((y1 - y2), 2))
        

    def _IRInfoToList(self, string): #nog niet getest.
        retVal = string.split(',')
        for num, val in enumerate(retVal):
            retVal[num] = int(val)
        return retVal 


        #returns all the locations our line crosses.
#     def _line_intersect_rect(self, x=0, y=0, angle=0):
#     	#als je y = ax hebt is dit die a
#     	a = 1/math.tan(angle) 
#     	#voor elk punt kijken of distance middenpunt_lijn< .5 dan gaat hij door hem heen, 
#     	#anders als distance > .5 sqrt(2) gaat hij niet doorheen en daartussen gewoon checken of de lijn
#     	#door zijn onderste of bovenste lijn heen gaat
#     	retVal = []
#     	retVal.append((x, y))


    def how_high(self): #werkt
        return len(self.matrixRC[0])

    def how_wide(self): #werkt
        return len(self.matrixRC)
        
    def debugPrint(self): #werkt
        return '\n'.join(str(row) for row in self.matrixRC)




    def beam(self, x, y, angle, distance):
        angle = -angle #this is because the y axis is inverted, so people can just put in non-inverted angles.
        a = math.atan(angle) # for the function ax - y + c = 0
        b = -1 #because of the way we set up this equation
        c = y - a*x
        retVal = []
#        print('test', a, b, c ) #Test
        ietsVakjes = [(X, Y) for X in range(self.rowsLen) for Y in range(self.collsLen) if self.matrixRC[X][Y] == 1]
#        print(ietsVakjes) #Test
        for vakje in ietsVakjes:
            d = math.fabs(a*vakje[0] + b*vakje[1] + c)/math.sqrt(a**2+b**2) #the distance between line and point
#            print('vakje is', vakje) #Test
#            print('d is', d) #Test
            while angle >(.5 * Pi):
                angle -= (.5 * Pi)
            while angle < 0:
                angle += (.5 * Pi)
            #this is needed for our next calculation to work, I want angle between 0 and .5 Pi
            if d <= math.sin(.25* Pi + angle)/math.sqrt(2):#the line hits the square.
                retVal.append(vakje)
        return retVal
            




    def how_far_line(self, x, y, angle): #werkt
    # met distance lijn, middenpunt vakje kun je een "hit zien"
    #De distance nodig voor een hit zut tussen sqrt(2)/2 en .5, deze distance hangt af van de hoek
    # omdat hij het blokje raken moet.
    #angle begint boven aan, telt in radialen en draait met de klok mee.
        # for the function ax - y + c = 0
        a = math.tan(angle+.5*Pi) #this is because 0 rad is on the top for us.
        b = -1 #because of the way we set up this equation
        c = y - a*x
        retVal = None
        if ( math.floor(angle/Pi)%2 == 0 ):
            right = True #test if the line is going to the right or to the left of the starting point.
        else: 
            right = False
#        print('test', a, b, c )
#        print('right =', str(right))
        ietsVakjes = [(X, Y) for X in range(self.rowsLen) for Y in range(self.collsLen) if self.matrixRC[X][Y] == 1]
#        print(ietsVakjes) #Test
        for vakje in ietsVakjes:
            if (vakje[0] >= x and right) or (vakje[0] <= x and not right):
                d = math.fabs(a*vakje[0] + b*vakje[1] + c)/math.sqrt(a**2+b**2) #the distance between line and point
#                print('vakje is', vakje)
#                print('d is', d) #test
                while angle >(.5 * Pi):
                    angle -= (.5 * Pi)
                while angle < 0:
                    angle += (.5 * Pi)
                #this is needed for our next calculation to work, I want angle between 0 and .5 Pi
#                 print('angle is', angle) #test
                if d <= math.sin(.25* Pi + angle)/math.sqrt(2):#the line hits the square.
#                    print('vakje is',vakje) #Test
                    foo = self._distance(x, y, vakje[0], vakje[1])
                    if retVal == None or foo < retVal: 
                        retVal = foo
        return retVal


    def how_far_free(self, x=0, y=0, angle=0, breedte=2):
        retVal = None
        for i in range(breedte+1):
            #I use negative angle cause the Y-axis is mirrored
            newX = math.cos(angle) * (i -.5 * breedte) + x
            newY = math.sin(angle) * (i -.5 * breedte) + y
            foo = self.how_far_line(newX, newY, angle)
            if (retVal == None or foo < retVal )and foo != None:
                retVal = foo
        return retVal


    def nearest_unknown(self, x, y):
        retVal = None
        unknownLocations = [(X, Y) for X in range(self.rowsLen) for Y in range(self.collsLen) if self.matrixRC[X][Y] == 2]
        for loc in unknownLocations:
            foo = self._distance(loc[0], loc[1], x, y)
            if retVal == None or foo < retVal:
                retVal = foo
        return retVal


    def combine(self, other, lbX, lbY): #lb = linksboven WIP!
        pass
        #(x,y)
        
        newLocations = []
        for i, r in enumerate(other.matrixRC):
            for j, c in enumerate(r):
                if self[i,j] == 1: 
                    pass
                elif other[i+lbX, j+lbY] == 1:
                    self[i,j] = 1
                elif self[i,j] == 2 and other[i+lbX, j+lbY] == 0:
                    self[i,j] = 0
        

















