//
// Created by davide on 12/03/18.
//

#include <malloc.h>
#include <cstdint>
#include "Buffer.h"

/*void Buffer::b2buffer(char source, char type, char dataSize, char *data, char *buffer) {
    buffer = new char[3+dataSize];
    buffer[0] = source;
    buffer[1] = type;
    buffer[2] = dataSize;
    for(int i=0; i<dataSize; i++){
        buffer[3+i] = data[i];
    }
}

Buffer Buffer::B2Buffer(char *buffer) {
    Buffer returnBuffer;
    returnBuffer.source = buffer[0];
    returnBuffer.type = buffer[1];
    returnBuffer.dataSize = buffer[2];
    returnBuffer.data = new char[returnBuffer.dataSize];
    for(int i=0; i<returnBuffer.dataSize; i++){
        returnBuffer.data[i] = buffer[3+i];
    }
    return Buffer();
}*/

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
    buffer = new uint8_t[length()];
    buffer[0] = source;
    buffer[1] = type;
    buffer[2] = dataSize;
    for(int i=0; i<dataSize; i++){
        buffer[3+i] = data[i];
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
    return dataSize+3;
}

Buffer::~Buffer() {
    delete[] data;
}
