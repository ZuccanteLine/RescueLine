#include <iostream>
#include <opencv2/opencv.hpp>
#include "LineFollower.h"
#include "communication/Uart.h"
#include "communication/Buffer.h"

#define CAMERA 0
#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#define THRESH 20
#define MAX_THRESH 255
#define EROSION_TYPE MORPH_RECT
#define EROSION_SIZE 3
#define MAX_EROSION_SIZE 10
#define DILATION_TYPE MORPH_RECT
#define DILATION_SIZE 2
#define MAX_DILATION_SIZE 10

#define DEBUG

typedef uint8_t byte;

/*int main() {
    cv::VideoCapture camera(CAMERA);
    cv::Mat image;

    LineFollower lineFollower;
    Uart uart("ttyACM0");

    while(true){
        camera.read(image);
        lineFollower.setImage(image);
    }

    return 0;
}*/

using std::cout;
using std::endl;

int main(){
    Buffer buffer;
    buffer.setSource(Buffer::source_enum::ARDUINO);
    buffer.setType(Buffer::type_enum::MOTORS);
    byte *ciao;
    ciao = new byte[3]; ciao[0]=111; ciao[1]=111;
    buffer.setData(ciao, 3);

    byte *hello;
    buffer.toBuffer(hello);
    for(int i=0; i<buffer.length(); i++){
        cout << i << "-" << (int)hello[i] << endl;
    }

    return 0;
}