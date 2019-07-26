import serial 
with serial.Serial('/dev/ttyACM0', 115200) as s:
    x = s.read()
    print(x)


