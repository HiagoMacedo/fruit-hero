#include "Fruit.h"

Fruit::Fruit() {
    x = 0;
    y = 0;
}

Fruit::Fruit(cv::Mat img) {
    image = img;
    x = 0;
    y = 0;
}

Fruit::Fruit(cv::Mat img, int xPos, int yPos) : Fruit(img) {
    x = xPos;
    y = yPos;
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

void Fruit::incrementY(int val) {
    y += val;
}
