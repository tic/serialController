from serial import Serial
from time import sleep

ser = Serial('/dev/ttyACM0', 9600) # ttyACM0 is the Arduino device | 9600 is baudrate

while True: # Read indefinitely
    bytesToRead = ser.inWaiting()
    lineIn = ser.read(bytesToRead).decode('ascii') # Read in bytes and decode to ascii
    if len(lineIn) > 0: # if nothing was read, skip
        for sym in lineIn: # view each read char individually
            print(sym) # print each char
    sleep(.005) # slow down the loop a little bit
