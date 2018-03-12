//
// Created by davide on 12/03/18.
//

#ifndef RESCUELINE_BUFFER_H
#define RESCUELINE_BUFFER_H

typedef uint8_t byte;

class Buffer {
private:
    byte source;
    byte type;
    byte dataSize;
    byte *data;

//    static void b2buffer(char source, char type, char size, char *data, char *buffer);
//    static Buffer B2Buffer(char *buffer);

public:
    enum source_enum{RASPBERRY, ARDUINO};
    enum type_enum{MOTORS, IMU};

    explicit Buffer(byte *buffer);
    explicit Buffer();
    virtual ~Buffer();

    byte getSource() const;
    byte getType() const;
    byte getDataSize() const;
    byte length();
    void getData(byte *&data);
    void cloneData(byte *&data);

    void setSource(byte source);
    void setType(byte type);
    void setData(byte *data, byte size);

    void toBuffer(byte *&buffer);
};


#endif //RESCUELINE_BUFFER_H
