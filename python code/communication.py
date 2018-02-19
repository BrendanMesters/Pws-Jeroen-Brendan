import serial
import time
ser = serial.Serial("/dev/ttyACM0")

def write(arg, answer = False):
    assert type(arg) == str
    retval = ser.write(str.encode(arg))
    if answer == True:
        return retval


def read(fullString = False, wait = False):
    retval = None
    if wait:
        while ser.inWaiting() == 0:
            pass
        retval = ser.readline()
    else:
        if ser.inWaiting() != 0:
            retval = ser.readline()
    if fullString:
        return retval
    elif retval != None:
        return retval.strip()


def readData():
    retval = []
    T1 = 0
    T2 = 0
    timeOut = False
    Finished = False
    timeOutTime = 10 #Time that has to pass befor we call a timeout
    while Finished == False and timeOut == False:
        foo = None
        ## TEST CODE!!!!1
#        foo = raw_input('input ')
        foo = read()
        if foo == 'OK':
            Finished = True
        elif foo == None:
            if T1 == 0:
                T1 = time.time()
            else:
                T2 = time.time()
                if T2-T1 >= timeOutTime:
                    timeOut = True
        else:
            T1, T2 = 0, 0
            assert foo.isdigit(), 'Unexpected serial readout'
            retval.append(int(foo))
    if timeOut:
        assert False, 'Timeout during readData()'
    return retval


def main_loop():
    while True:
        arg = raw_input("Wat wil je doen")
        if arg == 'Read' or arg == 'read':
            foo = read()
            if foo != None:
                print(foo)
        elif arg == 'Write' or arg == 'write':
            write(raw_input("Wat wil je schrijven").encode('utf-8'))
