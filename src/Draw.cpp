#include "Draw.h"
#include <vector>
#include <iostream>
#include <filesystem>
#include "Gerenciador.h"

using namespace std;

const int MIN_LANE = 0;
const int MAX_LANE = 3;

const int FRUIT_SPEED = 7;

const int ORANGE_LANE = 0;
const int PEAR_LANE = 1;
const int GRAPE_LANE = 2;
const int APPLE_LANE = 3;


Draw::Draw(std::string sequenceFile) 
{
    sequencePath = std::filesystem::current_path() / "sequences" / sequenceFile;
    Gerenciador ge(sequencePath.string());
    sequence = ge.read();
    sequenceHead = 0;
    currentLane = getNextSequence();
    points = 0;
    // randomNumGen.set(MIN_LANE, MAX_LANE);
    // currentLane = randomNumGen.get();
    
    orange = Fruit( imread("img/orange.png", IMREAD_UNCHANGED) );
    pear = Fruit( imread("img/pears_resized.png", IMREAD_UNCHANGED) );
    apple = Fruit( imread("img/apple_resized.png", IMREAD_UNCHANGED) );
    grape = Fruit(imread("img/grape_resized.png", IMREAD_UNCHANGED) );
    
    orange.setX(100);
    pear.setX(250);
    grape.setX(390);
    apple.setX(530);
    
}

void Draw::drawTransparency(Mat frame, Mat transp, int xPos, int yPos) {
    Mat mask;
    vector<Mat> layers;

    split(transp, layers); // seperate channels
    Mat rgb[3] = { layers[0],layers[1],layers[2] };
    mask = layers[3]; // png's alpha channel used as mask
    merge(rgb, 3, transp);  // put together the RGB channels, now transp insn't transparent 
    transp.copyTo(frame.rowRange(yPos, yPos + transp.rows).colRange(xPos, xPos + transp.cols), mask);

}

void Draw::drawTransRect(Mat frame, Scalar color, double alpha, Rect region) {
    Mat roi = frame(region);
    Mat rectImg(roi.size(), CV_8UC3, color); 
    addWeighted(rectImg, alpha, roi, 1.0 - alpha , 0, roi); 

}

void Draw::drawFruit(cv::Mat& smallImg, Fruit& f, Audio& audio) {
    drawTransparency(smallImg, f.getImage(), f.getX(), f.getY());

    if (f.getY() < (smallImg.rows - f.getImage().rows)-FRUIT_SPEED) {
        f.incrementY(FRUIT_SPEED);
    } 
    else {
        audio.playMiss();
        f.setY(0);
        // currentLane = randomNumGen.get();
        currentLane = getNextSequence();
    }
}

void Draw::detectAndDraw( Mat& img, CascadeClassifier& cascade, double scale, bool tryflip, Audio& audio) {
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg;
    Scalar color = Scalar(255,0,0);

    double fx = 1 / scale;
    resize( img, smallImg, Size(), fx, fx, INTER_LINEAR_EXACT );
    if( tryflip )
        flip(smallImg, smallImg, 1);
    cvtColor( smallImg, gray, COLOR_BGR2GRAY );
    equalizeHist( gray, gray );

    t = (double)getTickCount();

    cascade.detectMultiScale( gray, faces,
        1.3, 2, 0
        //|CASCADE_FIND_BIGGEST_OBJECT
        //|CASCADE_DO_ROUGH_SEARCH
        |CASCADE_SCALE_IMAGE,
        Size(70, 70) );
    t = (double)getTickCount() - t;
    // printf( "detection time = %g ms\n", t*1000/getTickFrequency());

    // Desenha uma imagem
    if (currentLane == ORANGE_LANE) {
        drawFruit(smallImg, orange, audio);
    }
    if (currentLane == PEAR_LANE) {
        drawFruit(smallImg, pear, audio);
    }
    if(currentLane == GRAPE_LANE) {
        drawFruit(smallImg, grape, audio);
    }
    if (currentLane == APPLE_LANE) {
        drawFruit(smallImg, apple, audio);
    }

    // PERCORRE AS FACES ENCONTRADAS
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        rectangle( smallImg, Point(cvRound(r.x), cvRound(r.y)),
                    Point(cvRound((r.x + r.width-1)), cvRound((r.y + r.height-1))),
                    color, 3);

        if (currentLane == ORANGE_LANE) {
            containsFruit(faces[0], orange, audio);
            break;
        }
        if (currentLane == PEAR_LANE) {
            containsFruit(faces[0], pear, audio);
            break;
        }
        if(currentLane == GRAPE_LANE) {
            containsFruit(faces[0], grape, audio);
            break;
        }
        if(currentLane == APPLE_LANE) {
            containsFruit(faces[0], apple, audio);
            break;
        }
    }

    drawLanes(smallImg);

    // Desenha um texto
    color = Scalar(0,0,255);
    putText	(smallImg, "Points: " + to_string(points), Point(10, 30), FONT_HERSHEY_PLAIN, 2, color, 2); // fonte

    // Desenha o frame na tela
    imshow("Fruit Hero", smallImg );
    // printf("image::width: %d, height=%d\n", smallImg.cols, smallImg.rows );
}

void Draw::drawLanes(Mat& smallImg) {
    double alpha = 0.3; 

    drawTransRect(smallImg, Scalar(0,255,255), alpha, Rect(100, 0, 120, smallImg.rows));
    drawTransRect(smallImg, Scalar(0,255,0), alpha, Rect(240, 0, 120, smallImg.rows));
    drawTransRect(smallImg, Scalar(255,0,0), alpha, Rect(380, 0, 120, smallImg.rows));
    drawTransRect(smallImg, Scalar(0,0,255), alpha, Rect(520, 0, 120, smallImg.rows));
}

bool Draw::containsFruit(Rect& r, Fruit& f, Audio& audio) {
    if( r.contains( cv::Point(f.getX(), f.getY()) ) ) {
        audio.playCorrect();
        updatePoints(f);
        return true;
    }
    return false;
}

void Draw::updatePoints(Fruit& f) {
    points++;
    f.setY(0);
    // currentLane = randomNumGen.get();
    currentLane = getNextSequence();
}

int Draw::getPoints() {
    return points;
}

int Draw::getNextSequence() {
    int next = stoi(sequence[sequenceHead]);
    sequenceHead++;
    return next;
}

void Draw::setCurrentLane(int cl) {
    currentLane = cl;
}