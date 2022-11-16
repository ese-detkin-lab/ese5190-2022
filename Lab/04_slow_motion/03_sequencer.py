import serial
import time

def write():
    s = serial.Serial('COM11', 115200, timeout=1)
    time.sleep(2)
    file = open("C:/Users/ABC/Desktop/sequence.txt", "w")
    print('Started writing')
    if s.is_open:
        read = str(s.readline())
        file.write(read)
        print(read)
        s.close()
        file.close()
    print('Finished writing')

while True:
    s = serial.Serial('COM11', 115200, timeout=1)
    print('Enter Input(r: record; n: normal replay; s: slow replay; f: fast replay):') 
    i = input()
    if(i == 'r'):
        time.sleep(2)
        s.write(b'r')
        print('Started recording the data sequence')
        s.close()
        time.sleep(10)
        print('Finished recording the data sequence')
    elif(i =='n'):
        time.sleep(2)
        print("Started replaying the data sequence at normal speed")
        s.write(b'p')
        s.close()
        write()
        time.sleep(2)
        print("Finished replaying the data sequence")
    elif(i =='s'):
        time.sleep(2)
        print("Started replaying the data sequence at slow speed")
        s.write(b's')
        s.close()
        write()
        time.sleep(2)
        print("Finished replaying the data sequence")
    elif(i =='f'):
        time.sleep(2)
        print("Started replaying the data sequence at fast speed")
        s.write(b'f')
        s.close()
        write()
        time.sleep(2)
        print("Finished replaying the data sequence")