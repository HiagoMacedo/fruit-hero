#include "FileNotOpenedException.h"

FileNotOpenedException::FileNotOpenedException(std::string msg)
{
    message = msg;
}

std::string FileNotOpenedException::what() {
    return message;
}