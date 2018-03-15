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

    lineFollower.add_analyzation_area(cv::Rect(0,0,640,480), 100);

    while(cv::waitKey(1)){
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        camera.read(image);
        lineFollower.setImage(image);
        lineFollower.process_average_black();

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