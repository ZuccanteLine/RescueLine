//
// Created by davide on 12/03/18.
//

#ifndef RESCUELINE_UART_H
#define RESCUELINE_UART_H


#include <termios.h>
#include <printf.h>
#include <fcntl.h>
#include <string>

class Uart {
public:
    explicit Uart(std::string device);
    bool read(uint8_t *buffer);
    bool write(uint8_t *buffer);
private:
    std::string device;
    struct termios toptions;
    int file;
};


#endif //RESCUELINE_UART_H
