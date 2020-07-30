import sys
import time
import serial

PORT, Baud = 'COM22', 9600


default_input_file = "me.txt"

if sys.argv.__len__() > 1:
    gcodefile = open(sys.argv[1])
else:
    gcodefile = open(default_input_file)

def gcodeCheck(line):
    # check if this is a valid gcode,
    # return false if the code is not valid.
    if line == "":
        print("Invalid G-Code Command:", line)
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

s = serial.Serial(PORT, Baud, timeout = 4)

# while True
#     cmd_lst = []
#     for cmd in range(10):
#         line = inputLine(gcodefile)
#         if line:
#             cmd_lst.append(cmd_lst)

#     s.write(cmd_lst)
line = inputLine(gcodefile)
# s.write("start".encode())
while line:
    print("Command:", line.strip())
    s.write((line+"\n").encode())
    # s.read()
    # while True:
    #     print(s.readline())
    #     if s.readline()=="complete":
    #         break
    thisline = s.readline()
    if(thisline):
        while True:
            thiscoolline = s.readline().decode().strip()
            if thiscoolline == "complete":
                print("complete")
                break
            else:
                print("Recieved:",thiscoolline)
    else:
        print("Timeout")
    line = inputLine(gcodefile)


gcodefile.close()