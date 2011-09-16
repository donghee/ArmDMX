import serial
import threading

SOM_VALUE = 0x7E
EOM_VALUE = 0xE7
OUTPUT_ONLY_SEND_DMX_LABEL = 6

class DMX:

    data_size = 513

    def __init__(self):       
        self.thread = None
        self.data = []
        self.writable = False
        self.ser = None
        self.alive = threading.Event()
    
    def open(self, _port):
        self.ser = serial.Serial(port=_port, baudrate=57600, timeout=1)
        self.turnoff()

    def turnoff(self):
        if self.ser.isOpen():
            data = [chr(0) for j in range(self.data_size)]
            self.write_all(data)
            
    def start_thread(self):
        """Start the transmit thread"""        
        self.thread = threading.Thread(target=self.tx_thread)
        self.thread.setDaemon(1)
        self.alive.set()
        self.thread.start()

    def stop_thread(self):
        """Stop the transmit thread, wait util it's finished."""
        if self.thread is not None:
            self.alive.clear()          #clear alive event for thread
            self.thread.join()          #wait until thread has finished
            self.thread = None
    
    def _write(self, label, data, data_size):
        if self.writable:
            self.ser.write(chr(SOM_VALUE))
            self.ser.write(chr(label))
            self.ser.write(chr(data_size & 0xFF))
            self.ser.write(chr((data_size >> 8) & 0xFF))
            for j in range(data_size):
                self.ser.write(self.data[j])
            self.ser.write(chr(EOM_VALUE))
            self.writable = False

    def write(self, ch, value):
        self.data[ch] = chr(value)

    def write_all(self, _data):
        self.data = _data
        self.writable = True

    def update(self):
        self.write_all(self.data)
        
    def tx_thread(self):
        while self.alive.isSet():
            self._write(OUTPUT_ONLY_SEND_DMX_LABEL, self.data, self.data_size)

    def close(self):
        self.ser.close()
