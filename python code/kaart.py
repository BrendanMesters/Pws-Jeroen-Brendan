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
    
    def __init__(self, rowsLen = 10, collsLen = 10): #werkt
        self.rowsLen = rowsLen
        self.collsLen = collsLen
        self.matrixRC = []
        for _ in range(rowsLen):
            self.matrixRC.append([2 for _ in range(collsLen)])


    def __str__(self): #werkt
#        retVal = '\n'.join(''.join(map(str, row)) for row in self.matrixRC) #Werkte niet zoals ik wilde
        retVal = str()
        for i in range(len(self.matrixRC)):
            retVal += '\n'
            for j in range(len(self.matrixRC[i])):
                retVal += str(self[j,i])
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




#     def beam(self, x, y, angle, distance):
#         #list of all squares our line passes.
#         retVal = [] 
#         
#         #we want the start location to not be located on the edge of two rectangles,
#         #this is a way to make sure that this won't happen
#     
#         
#         
#         # makes angle a value in between 0 and 2*Pi
#         while angle < 0:
#             angle += 2*pi
#         while angle > 2*Pi:
#             angle -= 2*Pi 
#         
#         
#         xRange = math.ceil(sin(angle))*distance
#         yValues = [x/math.tan(angle) for x in range(xRange)]
#         if not xRange.is_integer():
#             yValues.append(xRange.math.tan(angle))
#           
#         #ik kijk hier naar de met beginpunt (x, y), richting angle en lengte distance
#         #ik zal bij deze functie kijken wanneer de x een geheel getal is, als ik
#         #de y values op die locatie opsla (in de var yLocactions) dan weet ik dat
#         # de stukken daartussen geraakt worden.
#         
#         #naar rechtsboven
#         if angle > 0 and angle < .5*Pi: 
#             #we want the start location to not be located on the edge of two rectangles,
#             #this is a way to make sure that this won't happen (we'll be doing this 
#             #on every angle instance)
#             if x.is_integer():
#                 newX = x+.5
#             if y.is_integer():
#                 newY = x+.5
#             retVal.append(math.floor(x), math.floor(y))
#             
#             for num in range(1, len(yValues)):
#                 retVal.extend((num,Y+math.ceil(yValues[num-1])) for Y in range( math.ceil(yValues[num]-yValues[num-1] + 1)))
#             return retVal
#             
#             
#             
#         #naar rechtsonder
#         elif angle > .5*Pi and angle < Pi: 
#             if x.is_integer():
#                 x += .5
#             if y.is_integer():
#                 y += .5
#             
#           
#         #naar linksonder
#         elif angle > Pi and angle < 1.5*Pi: 
#             if x.is_integer():
#                 x -= .5
#             if y.is_integer():
#                 y += .5
#         
#         #naar linksbove
#         elif angle > 1.5*Pi and angle < 2*Pi: n
#             if x.is_integer():
#                 x -= .5
#             if y.is_integer():
#                 y -= .5
#                 
#         #other cases
#         else:
#             pass
            




    def how_far_line(self, x, y, angle): #werkt, maar de lijn gaat ook naar achteren, moet je fixen!!
    # met distance lijn, middenpunt vakje kun je een "hit zien"
    #De distance nodig voor een hit zut tussen sqrt(2)/2 en .5, deze distance hangt af van de hoek
    # omdat hij het blokje raken moet.
        a = math.atan(angle) # for the function ax - y + c = 0
        b = -1 #because of the way we set up this equation
        c = y - a*x
        retVal = None
        ietsVakjes = [(X, Y) for X in range(self.rowsLen) for Y in range(self.collsLen) if self.matrixRC[X][Y] == 1]
#        print(ietsVakjes) #Test
        for vakje in ietsVakjes:
            d = math.fabs(a*vakje[0] + b*vakje[1] + c)/math.sqrt(a**2+b**2) #the distance between line and point
            print('d is', d) #test
            while angle >(.5 * Pi):
                angle -= (.5 * Pi)
            while angle < 0:
                angle += (.5 * Pi)
            #this is needed for our next calculation to work, I want angle between 0 and .5 Pi
#             print('angle is', angle) #test
            if d <= math.sin(.25* Pi + angle)/math.sqrt(2):#the line hits the square.
#                 print('vakje is',vakje) #Test
                if retVal != None: 
                    retVal = min(retVal, self._distance(x, y, vakje[0], vakje[1]))
                else: 
                    retVal = self._distance(x, y, vakje[0], vakje[1])
        return retVal


    def how_far_free(self, x=0, y=0, angle=0, breedte=2):
        retVal = None
        for i in range(breedte+1):
            newX = math.sin(angle) * (i -.5 * breedte) + x
            newY = math.cos(angle) * (i -.5 * breedte) + y
            foo = self.how_far_line(newX, newY, angle)
            if retVal == None or foo < retVal:
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


    def combine(self, other, locationDefinement):
        pass

