
class Kaart:
    """ een matrix die de kaart van de auto aan gaat geven 0 is niets, 1 is iets
    en 2 is onbekend.
    !!!(2, 5) is de tweede rij en de vijfde colom!!!
    !!! colom telt van boven naar beneden, rij telt van links naar rechts!!!
    each pixel is one square cm
    """
    
    def __init__(self, rows = 10, colls = 10):
        self.matrixRC = []
        for _ in range(rows):
            self.matrixRC.append([2 for _ in range(colls)])


            
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


    def hoeHoog(self):
        return len(self.matrixRC[0])

    def hoeBreed(self):
        return len(self.matrixRC)

