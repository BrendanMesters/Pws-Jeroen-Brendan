"""
Test the distance the robot can drive in 30 seconds, than make the
maximum distance you tell him to drave smaler or equal to that distance
this is so that you can give an error message if the arduino has
not responded within 60 seconds after you send him a task, the
30 seconds extra time is just to make sure we don't get false
errors.
"""

"""
Arduino sends the sonar cencor information to me as a part of a a circle
(between 15 and 19 degrees there is an object with)
"""
import serial
import time
import math


ser = serial.Serial('/dev/cu.usbmodem621')


def read():
    Tbegin = time.time()
    while False == ser.in_waiting:
        if Tbegin < (time.time()-60):
            raise Exception('No message recieved from arduino while expecting a message')  #No return message in time.
    time.sleep(0.02)
    bitString = ser.read(ser.in_waiting)
    retVal = str(bitString.strip())
    retVal = retVal[2:-1]
    return retVal

def write(command = False, variable = False):
    assert (type(command) == str) and (type(variable) == int), 'Wrong/No input'
    serial.print(command + str(variable))


class matrix:
    """ een matrix die de kaart van de auto aan gaat geven 0 is niets, 1 is iets
    en 2 is onbekend.
    !!!(2, 5) is de tweede rij en de vijfde colom!!!
    !!! colom telt van boven naar beneden, rij telt van links naar rechts!!!
    each pixel is one square cm
    """
    
    def __init__(self, rows = 10, colls = 10):
        matrixRC = []
        for _ in range(rows):
            matrixRC.append([2 for _ in range(colls)])


            
    def _add(self, location = 0): #    0 = top; 1 = right; 2 = bot; 3 = left.
        if location = 0: #top
            for i in range(len(matrixRC)):
                matrixRC[i].insert(0, 2)
        elif location = 1: #right
            matrixRC.append([2 for _ in range( len( matrixRC(0) ) ) ])                      
        elif location = 2: #bottom
            for i in range(len(matrixRC)):
                matrixRC[i].append(2)
        elif location = 3: #left
            matrixRC.insert(0, [2 for _ in range( len( matrixRC(0) ) ) ] )
        else
            raise Exception('Wrong value for _add function in matrix, expected location to be between 0 and 3 got', location)


    def hoeHoog(self):
        return len(matrixRC[0])

    def hoeBreed(self):
        return len(matrixRC)




class Auto:
    """ Een object wat het autootje voorstelt, dit object heeft een kaart (matrix)
    deze matrix kan je aanvullen met nieuwe data die ik van de arduino krijg.
    de arduino praat met de py via de write en read functie, verder onthoud
    Auto de locatie van de fisieke auto en kan hij een nieuw pad voor de
    auto verzinnen aan de hand van de matrix en een complexe functie
    (er is een blaadje waar dit allemaal op staat uitgebeeld, Jeroen
    heeft dr ook nog een foto van.)"""

    def __init__(self):
        self.map = matrix(40, 40)
        self.location = (20, 20)


    def _verwerkenNieuweInfo(self):
        data = str()
        dataList = list()
        deltaLocaties = list()
        while True: #getting the data
            data +=  read()
            if data(-2:) = 'OK':
                break
        char = ''
        for i in range(len(data)): #changing data into a list
            char += data[-i]
            if data[-i] = , and char != '':#!!! het teken dat hier staat wordt gebruikt om de meet resultaten te scheiden!!!
                dataList.insert(0, char)
            elif data[-i] != ,:
                char.insert(0, data[-i])
        hoek = (len(dataList) / 360)
        for i, lengte in enumerate(datalist)
            if lengte <= 70:
                deltaLocaties.append((sin(i*hoek) * lengte, cos(i*hoek) * lengte))
        retval = matrix(141, 141) #71, 71 is the center point
        
        
        

        

        
        math.sin(hoek) * data = deltaX
        math.cos(hoek) * data = deltaY
    
