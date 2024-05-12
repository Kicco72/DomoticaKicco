# gestione dati 
# di Kicco972


import serial
import time

arduino = serial.Serial(
    port='COM5',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

time.sleep(1)

arduino.write(bytearray('S','ascii'))
time.sleep(.5)

print("pronto a ricevere")

while (True):
    print((arduino.readline()))
    time.sleep(.5)