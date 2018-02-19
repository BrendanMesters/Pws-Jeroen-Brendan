import serial
ser = serial.Serial("/dev/tty.usbmodem411")

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
        else:
            return retval.strip()

def main_loop():
    while True:
        arg = raw_input("Wat wil je doen")
        if arg == 'Read' or arg == 'read':
            foo = read()
            if foo != None:
                print(read())
        elif arg == 'Write' or arg == 'write':
            write(raw_input("Wat wil je schrijven").encode('utf-8'))
