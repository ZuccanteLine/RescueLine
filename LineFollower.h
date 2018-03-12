//
// Created by davide on 12/03/18.
//

#ifndef RESCUELINE_LINEFOLLOWER_H
#define RESCUELINE_LINEFOLLOWER_H


#include <opencv2/core/mat.hpp>

class LineFollower {
public:
    LineFollower();
    void setImage(cv::Mat image);
private:
    cv::Mat image;
};


#endif //RESCUELINE_LINEFOLLOWER_H
