//
// Created by Hiago on 23/09/2023.
//

#include "Gerenciador.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "../error/FileNotOpenedException.h"


Gerenciador::Gerenciador() {

}

Gerenciador::Gerenciador(std::string path) {
    this->path = path;
    bool exist = std::filesystem::exists(path);
    if (!exist) {
        fileStream.open(path, std::ios::out);
        fileStream << "Titanium" << std::endl;
        fileStream << "" << std::endl;
        fileStream << 0 << std::endl;
        fileStream << "Drive Breakbeat" << std::endl;
        fileStream << "" << std::endl;
        fileStream << 0;
        fileStream.close();
    }
}

void Gerenciador::create(std::vector<std::string> vec) {
    fileStream.open(path, std::ios::out);

    if (!fileStream.is_open()) {
        throw FileNotOpenedException("Arquivo não abriu!");
    }
    
    for (int i = 0; i < vec.size(); i++) {
        if (i == vec.size()-1) {
            fileStream << vec[i];
        }
        else {
            fileStream << vec[i] << std::endl;
        }
    }
    fileStream.close();
}

std::vector<std::string> Gerenciador::read() {
    std::vector<std::string> vec;
    std::string linha;

    fileStream.open(path, std::ios::in);
    if (!fileStream.is_open()) {
        throw FileNotOpenedException("Arquivo não abriu!");
    }
    while(!fileStream.eof()) {
        std::getline(fileStream, linha);
        vec.push_back(linha);
    }
    
    fileStream.close();
    return vec;
}

void Gerenciador::update(std::vector<std::string> vec) {
    fileStream.open(path, std::ios::app);
    if (!fileStream.is_open()) {
        throw FileNotOpenedException("Arquivo não abriu!");
    }
    for (auto linha : vec) {
        fileStream << linha << std::endl;
    }
    fileStream.close();
}

void Gerenciador::close() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

void Gerenciador::setPath(std::string p) {
    path = p;
}