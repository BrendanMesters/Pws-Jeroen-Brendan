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
import kaart



class Auto:
    """ Een object wat het autootje voorstelt, dit object heeft een kaart (matrix)
    deze matrix kan je aanvullen met nieuwe data die ik van de arduino krijg.
    de arduino praat met de py via de write en read functie, verder onthoud
    Auto de locatie van de fisieke auto en kan hij een nieuw pad voor de
    auto verzinnen aan de hand van de matrix en een complexe functie
    (er is een blaadje waar dit allemaal op staat uitgebeeld, Jeroen
    heeft dr ook nog een foto van.)"""

    def __init__(self):
        self.map = kaart.Kaart(40, 40)
        self.location = (20, 20)


    def _verwerkenNieuweInfo(self):
        data = str() #This will be the raw string we get from the cencor
        dataList = list() #This will be a list with all the information
        deltaLocaties = list() 
        while True: #getting the data
            data +=  read()
            if data[-2:] == 'OK':
                break
            assert not 'OK' in data
        char = ''
        #Puting the data into a list
        for i in range(len(data)):
            char += data[-i]
            if data[-i] == ',' and char != '':#data[-i] is nu dus ',' en scheid dus twee waarde
                dataList.insert(0, str(char))
            elif data[-i] != ',':
                char.insert(0, data[-i])
            else:
                assert False, 'Two devision symbols in a row'
        hoek = (len(dataList) / 360)
        
        #I am going to check the x value when y is a real number (for the linesfunction (y = a*x) from the IR scanner) than make the
        #smalest number the closest real number that is smaler and make the largest number the closest real number that is bigger,
        #we can say that the area between those points is empty.
        retVal = kaart.Kaart(101, 101)
        for i, j in enumerate(dataList):
            #This 'a' is the a in the function y = a*x this is used to calculate with.
            a = tan(90-i*hoek)
            #We don't want the 'lines' that go up, down, right or left.(at any quarter of the circle)
            if i % ((len(dataList)-1)*4) != 0:
                for k in range(math.floor(abs(cos(i*hoek)*j)-1)): #max hoogte/laagte
                    if k == math.floor(abs(cos(1*hoek)*j)):
                        dan = 1!!! foutief nog!!! (als j kleiner is dan onze minimale meet afstand dan is er dus iets (1))
                    Y1 = k
                    Y2 = k + 1
                    if Y2 > j: Y2 = j
                    X1 = math.floor(Y1/a)
                    X2 = math.ceil(Y2/a)
                    if cos(i*hoek) < 0:
                        Y1 = -Y1
                        Y2 = -Y2
                    if sin(i*hoek) < 0:
                        X1 = -X1
                        X2 = -X2
                    for j in range(abs(X2-X1)):
                                            
                    !!! niet af, voeg 0 in tussen x1 en x2




    
