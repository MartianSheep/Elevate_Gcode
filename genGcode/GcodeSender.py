import sys
import serial
import serial.tools.list_ports
from time import sleep

# defaults
default_input_file = "EE.txt"
baudrate = 9600

# available ports
ports = serial.tools.list_ports.comports()
print()
print("Available ports are: ")
for port, desc, hwid in sorted(ports):
    print("{}: {}".format(port, desc))
print()

# connecting ports
connected = False
while not connected:
    try:
        port = input("Please insert arduino nano port name: ")

        if port.upper() == "QUIT":
            print("Quit System")
            exit()

        print("Default baudrate is 9600.")
        ser = serial.Serial(port, baudrate, timeout = 4)
        print("Connection successed\n")
        connected = True
    except serial.serialutil.SerialException:
        print("Connection failed\n")
    except KeyboardInterrupt:
        print("\n\nUser Keyboard Interrupted")
        print("Exiting System")
        exit()

if sys.argv.__len__() > 1:
    print("Opening gcodefile: ", sys.argv[1])
    gcodefile = open(sys.argv[1])
else:
    print("Opening default gcodefile: ", default_input_file)
    gcodefile = open(default_input_file)

def gcodeCheck(line):
    # check if this is a valid gcode,
    # return false if the code is not valid.
    if line == "":
        print("Invalid G-Code Command: ", line)
        return False
    return True

def inputLine(file):
    while True:
        line = file.readline()
        if line == "":
            print("End Of File Reached. Tasks Completed.")
            return False
        line = line.strip()
        if line == "":
            continue
        if gcodeCheck(line):
            return line
        else:
            print("Invalid G-Code Command:", line)
            print("Reading the next Command...")

line = inputLine(gcodefile)

ser.write("start".encode()) # not important
time.sleep(2)

try:
    while line:
        print("Command: ", line.strip())
        ser.write((line+"\n").encode())
        thisline = ser.readline()
        if thisline:
            while True:
                thiscoolline = ser.readline().decode().strip()
                if thiscoolline == "complete":
                    print("complete")
                    break
                else:
                    print("Recieved: ",thiscoolline)
        else:
            print("Timeout")
        line = inputLine(gcodefile)
except KeyboardInterrupt:
    ser.close()
    gcodefile.close()
    print("User Keyboard Interrupted")
    print("System closed")
    exit()

gcodefile.close()
ser.close()