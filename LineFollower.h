//
// Created by davide on 12/03/18.
//

#ifndef RESCUELINE_LINEFOLLOWER_H
#define RESCUELINE_LINEFOLLOWER_H


#include <opencv2/core/mat.hpp>
#include <opencv/cv.hpp>

class LineFollower {
public:
    LineFollower();
    void setImage(cv::Mat image);

    void add_analyzation_area(cv::Rect area, int coefficient);

    //image analyse
    //--getter
    int getThresh() const;
    int getErosion_type() const;
    int getErosion_size() const;
    int getDilation_type() const;
    int getDilation_size() const;
    int16_t getRight() const;
    int16_t getLeft() const;
    //--setter
    void setThresh(int thresh);
    void setErosion_type(int erosion_type);
    void setErosion_size(int erosion_size);
    void setDilation_type(int dilation_type);
    void setDilation_size(int dilation_size);
    //--process
    void process_average_black();

    //debug
    void process_debug1();
    std::vector<std::vector<std::vector<cv::Point>>> get_all_contours(){
        return all_contours;
    }
    cv::Mat get_processed_image(){
        return processed_image;
    }
    std::vector<cv::Mat> get_cannied_areas(){
        return cannied_areas;
    }
    std::vector<cv::Point> get_average_point(){
        return average_points;
    }

private:
    cv::Mat image;
    int rows;
    int cols;

    //image analyse property
    int thresh = 20;
    int erosion_type = cv::MORPH_RECT;
    int erosion_size = 3;
    int dilation_type = cv::MORPH_RECT;
    int dilation_size = 2;
    cv::Mat erodeKernel;
    cv::Mat dilateKernel;

    //image analyse process
    std::vector<cv::Rect> analyzation_areas;
    std::vector<int> coefficients; //0-100
    std::vector<cv::Point> average_points;
    cv::Mat processed_image;
    void process_image();
    void find_black_average();
    //--contours
    std::vector<cv::Mat> cannied_areas;
    std::vector<std::vector<std::vector<cv::Point>>> all_contours;
    void extract_contours();
    //--motor
    int16_t right;
    int16_t left;
};


#endif //RESCUELINE_LINEFOLLOWER_H
