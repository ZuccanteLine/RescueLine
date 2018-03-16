import serial as se
import random
import string
#import smbus
import time


def write(slave, msg):
    # print "writing: " + msg + "\n"
    print len(msg)
    for ciao in msg:
        print ciao
    print "\n"
    slave.write(msg + '\n')


def read(slave):
    tmp = slave.readline().replace('\r\n', '')
    # print "Read: " + tmp
    return tmp


def init(port, baudrate, delay):
    slave = se.Serial(port, baudrate)
    time.sleep(delay)
    conn = False
    if type(slave) is se.serialposix.Serial:
        print "Verifico"
        for i in range(0, 10):
            str = 'start' + random.choice(string.ascii_uppercase)
            write(slave, str)
            if str == read(slave):
                write(slave, 'ok\n')
                conn = True
                break
            else:
                slave.write('no\n')
    if not conn:
        return False
    else:
        return slave
    return slave

def close(slave):
    slave.close()