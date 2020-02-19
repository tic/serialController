from serial import Serial
from serial.serialutil import SerialException
from time import sleep
import pyautogui, json

# Read in the byte map json file
def loadByteMap(mapfile='ByteMappings.json'):
    with open(mapfile) as f:
        return json.loads(f.read())
#

# Start serial connection
def loadSerial(device='/dev/ttyACM0', baudrate=9600):
    try:
        return Serial(device, baudrate)
    except SerialException as e:
        return None
#

# Synchronous function which returns after getting bytes from the serial device
def getSerialBytes(dev):
    # Read bytes from the serial device
    bytesInQueue = dev.inWaiting()

    # If the device had no input, keep checking until there is input.
    while bytesInQueue == 0:
        bytesInQueue = dev.inWaiting()
        sleep(.1)

    return dev.read(dev.inWaiting()).decode('ascii')
#

device = loadSerial()
if device is None:
    print("Serial device not found.")
    exit()

byte_map = loadByteMap('ByteMappings.json')

# Read bytes continually
try:
    while True:
        line_in = getSerialBytes(device)
        for char in line_in:
            try:
                key_info = byte_map[char]
                action = key_info["action"]
                key = key_info["key"]

                if action == "down":
                    pyautogui.keyDown(key)
                elif action == "up":
                    pyautogui.keyUp(key)

            except KeyError:
                print("Controller sent invalid byte: [" + char + "]")
except KeyboardInterrupt:
    print("\nNo longer listening to serial device.")
