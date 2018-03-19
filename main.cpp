#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include "LineFollower.h"
#include "communication/Uart.h"
#include "communication/Buffer.h"

#define CAMERA 0
#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#define ARDUINO_NAME "ttyACM0"

//#define MAX_THRESH 255
//#define MAX_EROSION_SIZE 10
//#define MAX_DILATION_SIZE 10
//#define DEBUG

int main() {
    cv::VideoCapture camera(CAMERA);
    cv::Mat image;

    LineFollower lineFollower;
    Uart uart(ARDUINO_NAME);
    Buffer buffer;
//    uint8_t *raw_buffer = new uint8_t[BUFFER_FIXED_DATA_SIZE + 3 +2];
    uint8_t *raw_buffer = new uint8_t[2];

    camera.set(CV_CAP_PROP_FRAME_WIDTH,CAMERA_WIDTH);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,CAMERA_HEIGHT);

//    lineFollower.add_analyzation_area(cv::Rect(0,0,640,480), 100);
    lineFollower.add_analyzation_area(cv::Rect(0 ,360,640,120), 100/8);

    buffer.setType(Buffer::TYPE_MOTORS);
    buffer.setSource(Buffer::SOURCE_RASPBERRY);

    while(cv::waitKey(1) == -1){
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));

//        camera.read(image);
//        lineFollower.setImage(image);
//        lineFollower.process_average_black();
//        buffer.setData(new uint8_t[4]{0,lineFollower.getLeft(),0,lineFollower.getRight()},4);
//        buffer.toBuffer(raw_buffer);
//        raw_buffer[7] = 10; // PERCHE FUNZIONA?????
//        raw_buffer[8] = 0;  // RAW_BUFFER È PIU PICCOLO DI 7 ED 8
    }

    return 0;
}