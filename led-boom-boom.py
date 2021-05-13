import serial
import time    #importing required libraries
close = 0      # 0 = connection open 1 = connection close
print("1 to turn led on \n0 to turn led off\n3 to rerun \n2 to close \n")     #printing general info regarding user-menu

arduino= serial.Serial("COM3",9600)
time.sleep(1)           #initialising connection with arduino
print("conn establsihed")
print(arduino.readline().decode("utf-8"))

while True:  #forever loop xD
    b=input()
    if b not in ["1","0","3","2"]:  #filtering out invalid responses
        print("Invalid Input")
        print()
        continue

    elif b == "3":
        if close == 0:              #mechanism to close a connection
            print("connection still active \n")
        else:
            arduino= serial.Serial("COM3",9600)
            time.sleep(1)
            print("conn establsihed")
            print(arduino.readline().decode("utf-8"))
            close = 0
        continue
    
    elif b == "2":
        if close == 1:
            print("connection already off \n")
        else:                       #mechanism to open/rerun a connection
            arduino.close()
            close = 1
            print("connection closed \n")
        continue

    elif b in ["1" , "0"] and close == 1:
        print("connection is closed please rerun \n")   #to prevent led operations after connection is off
        continue

    arduino.write(bytes(b.encode('ascii')))             #writing to arduino
    outP = arduino.readline()
    print(outP.decode("utf-8"))                         #displaying output by arduino
    print(arduino.readline().decode("utf-8"))
    time.sleep(0.5)                                     #sleep is important
#encoding converts string to bytes as arduino accepts input in byte form only
#decode converts input received from arduino in bytes form to user readable language
