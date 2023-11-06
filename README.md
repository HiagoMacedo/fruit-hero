# Fruit Hero Project

## About
Projeto feito para disciplina *'LABORATORIO DE LINGUAGEM DE PROGRAMAÇÃO I'* da UFPB do curso de Engenharia de Computação.
</br></br>
This project was done for the class *'LABORATORIO DE LINGUAGEM DE PROGRAMAÇÃO I'* at Universidade Federal da Paraíba (UFPB) for the Computer Engineering course.

## How to install SDL2_mixer
### Install SDL2_mixer
#### On Ubuntu:
On the command line first type: `` sudo apt-get install libsdl2-mixer-dev  `` </br>
After that you can type: `` sudo apt-get install libsdl2-mixer-2.0-0 `` </br>
If it fails to compile you can try to download the SDL2 library by using this command: `` sudo apt-get install libsdl2-dev ``

## How to Compile
**It needs C++17 and to have installed OpenCV and SDL2_mixer** </br>

To compile in Linux: </br> 
`` g++ main.cpp error/*.cpp src/*.cpp -I include/ -std=c++17 -lSDL2_mixer `pkg-config --cflags opencv4` `pkg-config --libs --static opencv4` ``

## Class Diagram
![](class_diagram/Class_diagram.png)