#include "Fruit.h"

Fruit::Fruit() {
    x = 0;
    y = 0;
}

Fruit::Fruit(cv::Mat img) {
    image = img;
    x = 0;
    y = 0;
    rectangle = Rect(0, 0, img.rows, img.cols);
}

Fruit::Fruit(cv::Mat img, int xPos, int yPos) : Fruit(img) {
    x = xPos;
    y = yPos;
    rectangle = Rect(xPos, yPos, img.rows, img.cols);
}

cv::Rect Fruit::getRectangle() {
    return rectangle;
}

void Fruit::setRectangle(cv::Rect rec) {
    rectangle = rec;
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
