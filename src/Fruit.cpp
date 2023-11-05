#include "Fruit.h"

Fruit::Fruit() {
    x = 0;
    y = 0;
    speed = 0;
}

Fruit::Fruit(cv::Mat img) : Fruit() {
    image = img;
}

Fruit::Fruit(cv::Mat img, int xPos, int yPos) : Fruit(img) {
    x = xPos;
    y = yPos;
}

void Fruit::setSpeed(int s) {
    speed = s;
}

cv::Mat Fruit::getImage() {
    return image;
}

void Fruit::setImage(cv::Mat img) {
    image = img;
}

void Fruit::setX(int xPos) {
    x = xPos;
}
    
int Fruit::getX() {
    return x;
}

void Fruit::setY(int yPos) {
    y = yPos;
}
    
int Fruit::getY() {
    return y;
}

void Fruit::increaseY() {
    y += speed;
}
