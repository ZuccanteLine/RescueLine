#include <opencv/cv.hpp>
#include <iostream>

using namespace std;
using namespace cv;


bool trackObject(Point &point, Mat &image){
    bool return_value;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(image, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

    return_value = false;

    if(contours.size()>0){
        if(contours.size()<10){
            for(int index = 0; index >=0; index = hierarchy[index][1]) {		// Changed 0 to 1 to return position of closest intead of farthest object.
                Moments moment = moments(contours[index]);
                int area = moment.m00;

                if(area>50){
                    point.x = moment.m10/area;
                    point.y = moment.m01/area;
                    return_value = true;
                } else{
                    return_value = false;
//                    point.x=0;
//                    point.y=0;
                }
            }
        } else cout << "Too much contours!" << endl;
    } else cout << "No contours!" << endl;
}

int main1(){
    VideoCapture cap(0);

    if (!cap.isOpened()){
        cout << "Cannot open the web cam" << endl;
        return -1;
    }

    namedWindow("Controls HSV", CV_WINDOW_AUTOSIZE);
//    namedWindow("Controls BGR", CV_WINDOW_AUTOSIZE); //create a window called "Control"

    int iLowH = 0;
    int iHighH = 179;
    int iLowS = 0;
    int iHighS = 255;
    int iLowV = 0;
    int iHighV = 255;

//    int iLowB = 0;
//    int iHighB = 255;
//    int iLowG = 0;
//    int iHighG = 255;
//    int iLowR = 0;
//    int iHighR = 255;

    int thresh1 = 20;
    int thresh2 = thresh1*2;

    cvCreateTrackbar("LowH", "Controls HSV", &iLowH, 179);
    cvCreateTrackbar("HighH", "Controls HSV", &iHighH, 179);
    cvCreateTrackbar("LowS", "Controls HSV", &iLowS, 255);
    cvCreateTrackbar("HighS", "Controls HSV", &iHighS, 255);
    cvCreateTrackbar("LowV", "Controls HSV", &iLowV, 255);
    cvCreateTrackbar("HighV", "Controls HSV", &iHighV, 255);

//    cvCreateTrackbar("LowB", "Controls BGR", &iLowB, 255);
//    cvCreateTrackbar("HighB", "Controls BGR", &iHighB, 255);
//    cvCreateTrackbar("LowG", "Controls BGR", &iLowG, 255);
//    cvCreateTrackbar("HighG", "Controls BGR", &iHighG, 255);
//    cvCreateTrackbar("LowR", "Controls BGR", &iLowR, 255);
//    cvCreateTrackbar("HighR", "Controls BGR", &iHighR, 255);

    cvCreateTrackbar("thresh1", "Control thresh", &thresh1, 255);
    cvCreateTrackbar("thresh2", "Control thresh", &thresh2, 255);

    Point point(0,0);

    while(waitKey(1) != 27){
        Mat imgOriginal;
        cap.read(imgOriginal);

        Mat imgHSV, imgHSVcannied;
//        Mat imgBGR, imgBGRcannied;

        cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);

        inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgHSV);
//        inRange(imgOriginal, Scalar(iLowB, iLowG, iLowR), Scalar(iHighB, iHighG, iHighR), imgBGR);

        erode(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        dilate(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
        erode(imgHSV, imgHSV, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

//        erode(imgBGR, imgBGR, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//        dilate(imgBGR, imgBGR, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//        dilate(imgBGR, imgBGR, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//        erode(imgBGR, imgBGR, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
//
        Canny(imgHSV, imgHSVcannied, thresh1, thresh2);
//        Canny(imgBGR, imgBGRcannied, thresh1, thresh2);

        imshow("HSV thresholded image", imgHSV);
//        imshow("BGR thresholded image", imgBGR);
        imshow("HSV cannied image", imgHSVcannied);
//        imshow("BGR cannied image", imgBGRcannied);
        imshow("Original", imgOriginal);


//        if(trackObject(point,imgHSV)) rectangle(point.x, point.y, imgOriginal, Scalar(0,255,0));
        if(trackObject(point,imgHSVcannied)) rectangle(imgOriginal, Rect(point.x-10, point.y-10, point.x+10, point.y+10), Scalar(0,0,255), 2, LINE_8);
//        if(objectFound==true && show_images==1) drawObject( green_x, green_y, image, Scalar( 0, 255, 0 ));
    }

}