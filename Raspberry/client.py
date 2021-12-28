import socket
import constants
import serial
import time
from datetime import date, datetime
import errno
import select
from socket import error as socket_error

#print("======================================")
#print("Setting up Serial between Raspberry Pi and Leonardo.")
#ser = serial.Serial(constants.SERIAL_PORT, constants.SERIAL_BUADRATE)
#print("Serial port information: ")
#print("    Port: " + str(constants.SERIAL_PORT))
#print("    Buadrate: " + str(constants.SERIAL_BUADRATE))

serverAddressPort = (constants.SERVER_UDP_IP, constants.SERVER_UDP_PORT)
# Create a UDP socket at client side
clientSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
clientSock.bind(('', 30020))
clientSock.setblocking(0)
print("======================================")
print("UDP client setup and ready to communicate")

def processData(dataRecvd):
    #Split only first seperator, then route data
    splitData = dataRecvd.split(',', 1)
    if (splitData[0] == 'm'):
        print("MOVEMENT")
        # Movement data
        # Send serial movement data to arduino
        #dataToSend = ('<'+splitData[1]+'>').encode('utf-8')
        #ser.write(dataToSend)

    if (splitData[0] == 's'):
        print("STATUS")
        # Status
        # Send data back to server with % and others

    if (splitData[0] == 'g'):
        print("GYRO")
        # Gyro
        # (Unsure if this will be connected to the raspberry pi or arduino)

while(True):
    try:
        # Send to server using created UDP socket
        dataSend = "" # Keep Alive
        print("[{}:{}:{}] S {} <- {}".format(datetime.now().hour, datetime.now().minute, datetime.now().second, serverAddressPort, dataSend))
        clientSock.sendto(str.encode(dataSend), serverAddressPort)

        # Recieve with a timeout (in this case 1s)
        dataReady = select.select([clientSock], [], [], 0.25)
        if dataReady[0]:
            dataRecvdTupl = clientSock.recvfrom(constants.BUFFER_SIZE)
            dataRecvd = dataRecvdTupl[0].decode("utf-8")
            print("[{}:{}:{}] R {} -> {}".format(datetime.now().hour, datetime.now().minute, datetime.now().second, dataRecvdTupl[1], dataRecvd))
            processData(dataRecvd)

    except socket_error as e:
        #Riase error if its not a connection error
        if e.errno == errno.ECONNREFUSED:
            print("[{}:{}:{}] Error: Connection refused".format(datetime.now().hour, datetime.now().minute, datetime.now().second))
        elif e.errno == errno.WSAECONNRESET:
            print("[{}:{}:{}] Error: Connection forcibly closed".format(datetime.now().hour, datetime.now().minute, datetime.now().second))
        else:
            raise e
        time.sleep(1)

    
