//
// Created by Hiago on 23/09/2023.
//

#pragma once
#include <fstream>
#include <string>
#include <vector>

class Gerenciador {
public:
    Gerenciador();
    Gerenciador(std::string path);
    void create(std::vector<std::string> vec);
    std::vector<std::string> read();
    void update(std::vector<std::string> vec);
    void deletar();
    void close();
    void setPath(std::string p);
private:
    std::fstream fileStream;
    std::string path;
};


