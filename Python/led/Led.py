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

while (True):
    val = input("comando: ")
    arduino.write(val.encode())
    