#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include "LineFollower.h"
#include "communication/Uart.h"

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

    camera.set(CV_CAP_PROP_FRAME_WIDTH,CAMERA_WIDTH);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,CAMERA_HEIGHT);

    //    lineFollower.set...;
    lineFollower.add_analyzation_area(cv::Rect(0,0,640,480), 1);

    while(cv::waitKey(1)){
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        camera.read(image);
        lineFollower.setImage(image);
        lineFollower.process1();
        for(auto contours : lineFollower.get_all_contours()){
            try{
                cv::drawContours(image, contours, 0, cv::Scalar(0,0,255), 3, 8, NULL, 0);
//                std::cout << "Un contorno" << std::endl;
            } catch (std::exception ex){
                std::cout << "Eccezione :)" << std::endl;
            }
        }
        cv::imshow("Image", image);
        cv::imshow("Processed image", lineFollower.get_processed_image());
    }

    return 0;
}

/*
using std::cout;
using std::endl;

int main(){
    Buffer buffer;
    buffer.setSource(Buffer::source_enum::ARDUINO);
    buffer.setType(Buffer::type_enum::MOTORS);
    uint8_t *ciao;
    ciao = new uint8_t[3]; ciao[0]=111; ciao[1]=111;
    buffer.setData(ciao, 3);

    uint8_t *hello;
    buffer.toBuffer(hello);
    for(int i=0; i<buffer.length(); i++){
        cout << i << "-" << (int)hello[i] << endl;
    }

    return 0;
}*/