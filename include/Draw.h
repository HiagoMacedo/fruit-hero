#pragma once
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "UniformRandomInt.h"
#include "Fruit.h"
#include "Game.h"
#include "Audio.h"
#include <vector>
#include <string>
#include <filesystem>

using namespace cv;


class Draw
{
public:
    Draw(std::string sequenceFile);

    void drawTransparency(Mat frame, Mat transp, int xPos, int yPos);

    void drawTransRect(Mat frame, Scalar color, double alpha, Rect region);

    void detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip, Audio& audio);
    
    void drawFruit(Mat& smallImg, Fruit& f, Audio& audio);

    void drawLanes(Mat& smallImg);

    bool containsFruit(Rect& r, Fruit& f, Audio& audio);

    void updatePoints(Fruit& f);

    int getPoints();

    int getNextSequence();

private:
    int currentLane;
    int points;
    Fruit pear;
    Fruit orange;
    Fruit apple;
    Fruit grape;
    std::vector<std::string> sequence;
    int sequenceHead;
    // std::filesystem::path sequencePath;
    // UniformRandomInt randomNumGen;
};