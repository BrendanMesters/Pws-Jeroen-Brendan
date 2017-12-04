import serial
import time

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