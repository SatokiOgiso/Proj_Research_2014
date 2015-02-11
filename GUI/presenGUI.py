import serial 


def main():
    ser = serial.Serial(port = 'COM8', baudrate = 9600) # serial port initialization
    recvWord = []
    
    try:
        while True:
            while ser.inWaiting() > 0:
                recvWord.append(ser.read(1))
                if recvWord[-1] == '\n': # if the word was completed
                    dataset = "".join(recvWord)
                    print dataset
                    recvWord = []
                    
    except KeyboardInterrupt:
        print 'end'
            
    ser.close()
    print 'serial port closed'

            
if __name__ == '__main__':
    main()
