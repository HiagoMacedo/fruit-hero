#pragma once
#include <string>

class MusicNotLoadedException
{
public:
    MusicNotLoadedException(std::string msg);

    std::string what();

private:
    std::string message;
};