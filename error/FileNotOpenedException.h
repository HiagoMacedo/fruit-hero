#pragma once
#include <string>
#include <exception>

class FileNotOpenedException : public std::exception
{
public:
    FileNotOpenedException(std::string msg);
    std::string what();
private:
    std::string message;
};