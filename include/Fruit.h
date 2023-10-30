#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"

using namespace cv;

class Fruit
{
public:
    Fruit();
    Fruit(cv::Mat img);
    Fruit(cv::Mat img, int xPos, int yPos);

    void incrementY(int val);

    cv::Mat getImage();

    void setImage(cv::Mat img);

    void setX(int xPos);
    
    int getX();

    void setY(int yPos);
    
    int getY();

private:
    cv::Mat image;
    int x;
    int y;
};