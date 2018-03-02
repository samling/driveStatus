import serial
import socket
import subprocess
import time

ser = serial.Serial(
    port='/dev/ttyACM0',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    xonxoff=serial.XOFF,
    rtscts=False,
    dsrdtr=False
)
ser.isOpen()

df = subprocess.Popen(["df", "/home/pi/callisto", "/home/pi/europa", "/home/pi/ganymede"], stdout=subprocess.PIPE)
drives = df.communicate()[0]
device1, size1, used1, available1, percent1, mountpoint1 = drives.split("\n")[1].split()
device2, size2, used2, available2, percent2, mountpoint2 = drives.split("\n")[2].split()
device3, size3, used3, available3, percent3, mountpoint3 = drives.split("\n")[3].split()

def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('10.255.255.255', 1))
        IP = s.getsockname()[0]
    except:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP

ip = get_ip()

if ser.isOpen():
	ser.flush()
	ser.write(device1 + ":" + mountpoint1 + ":" + size1 + ":" + used1 + ":" + available1 + ":" + percent1 + "&")
	time.sleep(1)
	ser.write(device2 + ":" + mountpoint2 + ":" + size2 + ":" + used2 + ":" + available2 + ":" + percent2 + "&")
	time.sleep(1)
	ser.write(device3 + ":" + mountpoint3 + ":" + size3 + ":" + used3 + ":" + available3 + ":" + percent3 + "&")
	print(ip)
	ser.write(ip+"&")
	ser.close()

ser.close()
