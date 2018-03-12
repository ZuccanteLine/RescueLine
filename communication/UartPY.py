import serial as se
import random
import string
#import smbus
import time


def write(slave, msg):
    slave.write(msg + '\n')


def read(slave):
    return slave.readline().replace('\r\n', '')


def init(port, baudrate, delay):
    slave = se.Serial(port, baudrate)
    time.sleep(delay)
    conn = False
    if type(slave) is se.serialposix.Serial:
        for i in range(0, 10):
            str = 'start' + random.choice(string.ascii_uppercase)
            write(slave, str)
            if str == read(slave):
                # slave.write('ok\n')
                conn = True
                break
            # else:
            #     slave.write('no\n')
    if not conn:
        return False
    else:
        return slave


def close(slave):
    slave.close()