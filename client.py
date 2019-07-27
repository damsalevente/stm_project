import serial 
with serial.Serial('/dev/ttyACM0', 115200) as s:
    while(True):
      x = s.readline()
      print(x)

