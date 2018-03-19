//
// Created by davide on 12/03/18.
//

#include <cstdint>
#include "Buffer.h"

uint8_t Buffer::getSource() const {
    return source;
}

uint8_t Buffer::getType() const {
    return type;
}

uint8_t Buffer::getDataSize() const {
    return dataSize;
}

void Buffer::getData(uint8_t *&data) {
    data = Buffer::data;
}

void Buffer::setSource(uint8_t source) {
    Buffer::source = source;
}

void Buffer::setType(uint8_t type) {
    Buffer::type = type;
}

void Buffer::setData(uint8_t *data, uint8_t size) {
    Buffer::dataSize = size;
    Buffer::data = new uint8_t[size];
    for(int i=0; i<size; i++){
        Buffer::data[i] = data[i];
    }
}

void Buffer::cloneData(uint8_t *&data) {
    data = new uint8_t[dataSize];
    for(int i=0; i<dataSize; i++){
        data[i] = Buffer::data[i];
    }
}

void Buffer::toBuffer(uint8_t *&buffer) {
//    buffer = new uint8_t[length()]; //DA FIXARE
    buffer = new uint8_t[length()];

    int i=0;
    buffer[i] = source;
    i++;
    buffer[i] = type;
    i++;
    buffer[i] = dataSize;
    i++;
    for(; i<dataSize; i++){
        buffer[getHeaderSize()+i] = data[i];
    }
}

Buffer::Buffer(uint8_t *buffer) {
    source = buffer[0];
    type = buffer[1];
    dataSize = buffer[2];
    data = new uint8_t[dataSize];
    for(int i=0; i<dataSize; i++){
        data[i] = buffer[3+i];
    }
}

Buffer::Buffer() {
}

uint8_t Buffer::length() {
    return getDataSize()+getHeaderSize();
}

Buffer::~Buffer() {
    delete[] data;
}

uint8_t Buffer::getHeaderSize() const {
    return 3; //DA SISTEMARE
}
