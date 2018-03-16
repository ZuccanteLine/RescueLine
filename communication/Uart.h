//
// Created by davide on 12/03/18.
//

#ifndef RESCUELINE_UART_H
#define RESCUELINE_UART_H

#define BUFFER_FIXED_DATA_SIZE 4

#include <termios.h>
#include <printf.h>
#include <fcntl.h>
#include <string>

class Uart {
public:
    explicit Uart(std::string device);
    bool _read(uint8_t *buffer, int size);
    bool _write(uint8_t *buffer, int size);
private:
    std::string device;
    struct termios toptions;
    int file;
};


#endif //RESCUELINE_UART_H
