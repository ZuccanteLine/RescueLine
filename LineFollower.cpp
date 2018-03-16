//
// Created by davide on 12/03/18.
//

#include <iostream>
#include "LineFollower.h"

void LineFollower::setImage(cv::Mat image) {
    LineFollower::image = image.clone();
    rows = image.rows;
    cols = image.cols;
}

int LineFollower::getThresh() const {
    return thresh;
}

int LineFollower::getErosion_type() const {
    return erosion_type;
}

int LineFollower::getErosion_size() const {
    return erosion_size;
}

int LineFollower::getDilation_type() const {
    return dilation_type;
}

int LineFollower::getDilation_size() const {
    return dilation_size;
}

void LineFollower::setThresh(int thresh) {
    LineFollower::thresh = thresh;
}

void LineFollower::setErosion_type(int erosion_type) {
    LineFollower::erosion_type = erosion_type;
    erodeKernel = cv::getStructuringElement(erosion_type, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), cv::Point(erosion_size, erosion_size));
}

void LineFollower::setErosion_size(int erosion_size) {
    LineFollower::erosion_size = erosion_size;
    erodeKernel = cv::getStructuringElement(erosion_type, cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1), cv::Point(erosion_size, erosion_size));
}

void LineFollower::setDilation_type(int dilation_type) {
    LineFollower::dilation_type = dilation_type;
    dilateKernel = cv::getStructuringElement(dilation_type, cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1), cv::Point(dilation_size, dilation_size));
}

void LineFollower::setDilation_size(int dilation_size) {
    LineFollower::dilation_size = dilation_size;
    dilateKernel = cv::getStructuringElement(dilation_type, cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1), cv::Point(dilation_size, dilation_size));
}

LineFollower::LineFollower() {

}

int16_t LineFollower::getRight() const {
    return right;
}

int16_t LineFollower::getLeft() const {
    return left;
}


void LineFollower::process_image() {
//    cv::Mat processed = Mat(image, rettangolo); // estrapolo solo l'area interessata
    cv::cvtColor(image, processed_image, CV_BGR2GRAY); // converto in bianco e nero
    cv::GaussianBlur(processed_image, processed_image, cv::Size(9, 9), 2, 2); // sfoco leggermente l'immagine per ridurre gli "zig e zag"
    cv::threshold(processed_image, processed_image, thresh, 255, 0); // converto tutto in bianco o nero
    cv::erode(processed_image, processed_image, erodeKernel); // elimino le "impurità"
    cv::dilate(processed_image, processed_image, dilateKernel); // ri espando l'immagine
}

void LineFollower::add_analyzation_area(cv::Rect area, int coefficient) {
    analyzation_areas.push_back(cv::Rect(area));
    coefficients.push_back(coefficient);
}

void LineFollower::extract_contours() {
    all_contours.clear();
    cannied_areas.clear();
    for(cv::Rect area : analyzation_areas){
        std::vector<std::vector<cv::Point>> contours;
        cannied_areas.push_back(cv::Mat(processed_image, area).clone());
        cv::Canny(cannied_areas.back(), cannied_areas.back(), thresh, thresh * 2, 3);
        cv::findContours(cannied_areas.back(), contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
        all_contours.push_back(contours);
    }
//    for(auto contours : all_contours){
//        for(auto contour : contours){
//
//        }
//    }
}

void LineFollower::process_debug1() {
    process_image();
    extract_contours();
//    for(cv::Rect area : analyzation_areas){
//        std::vector<std::vector<cv::Point>> contours;
//        cv::Mat cannied_image(processed_image, area);
//        cv::Canny(cannied_image, cannied_image, thresh, thresh*2, 3);
//        cv::findContours(cannied_image, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
//    }
//    cv::imshow("Ciao1", processed_image);
}

void LineFollower::find_black_average() {
    average_points.clear();
    for(cv::Rect area : analyzation_areas) {
        cv::Mat matTmp = cv::Mat(processed_image, area).clone();
//        cv::imshow("caio", matTmp);
        long long int average_x = 0, average_y = 0;
        int counter = 0;
        for (int x = 0; x <= matTmp.cols; x++) {
            for (int y = 0; y <= matTmp.rows; y++) {
                if (matTmp.at<uchar>(y, x) == 0) {
                    average_x += x;
                    average_y += y;
                    counter++;
                }
            }
        }
        average_points.push_back(cv::Point(average_x/counter, average_y/counter));
    }
}

void LineFollower::process_average_black() {
    process_image();
    find_black_average();

    right=0; left=0;
    double tmp;
    for(int i=0; i<analyzation_areas.size(); i++){
        tmp = average_points.at(i).x;
//        std::cout << tmp << "\t";
        tmp = (tmp/cols)*255;
//        std::cout << tmp << "\t";
        tmp = (tmp/100)*coefficients.at(i);
//        std::cout << tmp << "\t";
        tmp = tmp/analyzation_areas.size();
//        std::cout << tmp << "\n";
        right += ((tmp)/(100*analyzation_areas.size()))*coefficients.at(i);
        left += 255 - ((tmp)/(100*analyzation_areas.size()))*coefficients.at(i);
    }
}
