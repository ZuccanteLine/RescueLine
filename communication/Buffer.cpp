//
// Created by davide on 12/03/18.
//

#include <malloc.h>
#include <cstdint>
#include "Buffer.h"

typedef uint8_t byte;

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

byte Buffer::getSource() const {
    return source;
}

byte Buffer::getType() const {
    return type;
}

byte Buffer::getDataSize() const {
    return dataSize;
}

void Buffer::getData(byte *&data) {
    data = Buffer::data;
}

void Buffer::setSource(byte source) {
    Buffer::source = source;
}

void Buffer::setType(byte type) {
    Buffer::type = type;
}

void Buffer::setData(byte *data, byte size) {
    Buffer::dataSize = size;
    Buffer::data = new byte[size];
    for(int i=0; i<size; i++){
        Buffer::data[i] = data[i];
    }
}

void Buffer::cloneData(byte *&data) {
    data = new byte[dataSize];
    for(int i=0; i<dataSize; i++){
        data[i] = Buffer::data[i];
    }
}

void Buffer::toBuffer(byte *&buffer) {
    buffer = new byte[length()];
    buffer[0] = source;
    buffer[1] = type;
    buffer[2] = dataSize;
    for(int i=0; i<dataSize; i++){
        buffer[3+i] = data[i];
    }
}

Buffer::Buffer(byte *buffer) {
    source = buffer[0];
    type = buffer[1];
    dataSize = buffer[2];
    data = new byte[dataSize];
    for(int i=0; i<dataSize; i++){
        data[i] = buffer[3+i];
    }
}

Buffer::Buffer() {
}

byte Buffer::length() {
    return dataSize+3;
}

Buffer::~Buffer() {
    delete[] data;
}
