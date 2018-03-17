#include <iostream>
#include <opencv2/opencv.hpp>
#include <thread>
#include "LineFollower.h"
#include "communication/Uart.h"
#include "communication/Buffer.h"
#include "communication/UartPY.cpp"

#define CAMERA 0
#define CAMERA_WIDTH 640
#define CAMERA_HEIGHT 480

#define ARDUINO_NAME "ttyACM0"

//#define MAX_THRESH 255
//#define MAX_EROSION_SIZE 10
//#define MAX_DILATION_SIZE 10
//#define DEBUG

int main() {
    cout << "ciao" << endl;
    cv::VideoCapture camera(CAMERA);
    cv::Mat image;

    LineFollower lineFollower;
//    Uart uart(ARDUINO_NAME);
    UartConnection uart(115200, ARDUINO_NAME);
    Buffer buffer;
    uint8_t *raw_buffer = new uint8_t[BUFFER_FIXED_DATA_SIZE + 3 +2];

    camera.set(CV_CAP_PROP_FRAME_WIDTH,CAMERA_WIDTH);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT,CAMERA_HEIGHT);

//    lineFollower.add_analyzation_area(cv::Rect(0,0,640,480), 100);
    lineFollower.add_analyzation_area(cv::Rect(0 ,360,640,120), 100/8);

    buffer.setType(Buffer::TYPE_MOTORS);
    buffer.setSource(Buffer::SOURCE_RASPBERRY);

    /*int left, right;
    while(true){
        cout << "Left: ";
        std::cin >> left;
        cout << "Right: ";
        std::cin >> right;
        buffer.setData(new uint8_t[4]{0,left,0,right}, 4);
        buffer.toBuffer(raw_buffer);
        raw_buffer[7] = 10;
        raw_buffer[8] = 0;
        uart._write(std::string((char*)raw_buffer, 9));
        std::string ciao = uart._read();
        cout << "uart._read.size(): " << ciao.size() << endl;
        for(int i=0; i<ciao.size(); i++){
            cout << i << "-" << (int)ciao.at(i) << endl;
        }
    }*/
    while(cv::waitKey(1) == -1){
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        camera.read(image);
        lineFollower.setImage(image);
        lineFollower.process_average_black();
        buffer.setData(new uint8_t[4]{0,lineFollower.getLeft(),0,lineFollower.getRight()},4);
//        buffer.setData(new uint8_t[4]{0,123,0,lineFollower.getRight()},4);
        buffer.toBuffer(raw_buffer);
        raw_buffer[7] = 10; // PERCHE FUNZIONA?????
        raw_buffer[8] = 0;  // RAW_BUFFER È PIU PICCOLO DI 7 ED 8

        //prova2 comunicazione
//        for(int i=0; i<9; i++) cout << (int)raw_buffer[i] << "\t";
//        cout << endl;
//        cout << "string size: " << std::string((char*)raw_buffer, 9).size() << endl;
//        for(int i=0; i<9; i++) cout << (int)std::string((char*)raw_buffer, 9).at(i) << "\t";
//        cout << "\n";

        uart._write(std::string((char*)raw_buffer, 9));
        raw_buffer = (uint8_t*)uart._read().c_str();
        cout << "Read: ";
        for(int i=0; i<8; i++) cout << (int)raw_buffer[i] << "\t";
        cout << "\n";

        //prova1 comunicazione
        /*uart._write(raw_buffer, BUFFER_FIXED_DATA_SIZE+3);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        uint8_t *ciao = new uint8_t[7];
        uart._read(ciao, 7);
        std::cout << "Buffer: " << (int)ciao[0];
        std::cout << "-" << (int)ciao[1];
        std::cout << "-"<< (int)ciao[2];
        std::cout << "-" << (int)ciao[3];
        std::cout << "-" << (int)ciao[4] << "\n";*/

        //debug
        std::cout << lineFollower.getRight() << "\t";
        std::cout << lineFollower.getLeft() << "\n";
        cv::circle(image, lineFollower.get_average_point().at(0), 3, cv::Scalar(0,0,255), 3, cv::LINE_8);
        cv::imshow("Ciaoooo", image);

//        lineFollower.process_debug1();
//        for(auto contours : lineFollower.get_all_contours()){
//            for(int i=0; i<contours.size(); i++) {
//                try {
//                    cv::drawContours(image, contours, i, cv::Scalar(0, 0, 255), 3, 8, NULL, 0);
//                } catch (std::exception ex) {
//                    std::cout << "Eccezione :)" << std::endl;
//                }
//            }
//        }
//        cv::imshow("Cannied", lineFollower.get_cannied_areas().at(0));
//        cv::imshow("Image", image);
//        cv::imshow("Processed image", lineFollower.get_processed_image());
    }

    return 0;
}