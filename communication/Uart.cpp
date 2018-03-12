//
// Created by davide on 12/03/18.
//

#include "Uart.h"

Uart::Uart(std::string device){
    file = open(("/dev/" + device).c_str(), O_RDWR | O_NOCTTY);
    tcgetattr(file, &toptions);
//        printf("%d\t", cfgetispeed(&toptions));
    cfsetispeed(&toptions, B19200);
//        printf("%d\n", cfgetispeed(&toptions));
//        printf("%d\t", cfgetospeed(&toptions));
    cfsetospeed(&toptions, B19200);
//        printf("%d\n", cfgetospeed(&toptions));
//        printf("%d\t", toptions.c_cflag);
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;
//        printf("%d\n", toptions.c_cflag);
//        printf("%d\t", toptions.c_lflag);
    //toptions.c_lflag |= ICANON;
    toptions.c_lflag = 0;
    printf("%d\n", toptions.c_lflag);
    tcsetattr(file, TCSANOW, &toptions);
}

bool Uart::read(byte *buffer) {
    
    return true;
}

