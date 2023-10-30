#include "MusicNotLoadedException.h"

MusicNotLoadedException::MusicNotLoadedException(std::string msg)
{
    message = msg;
}

std::string MusicNotLoadedException::what() {
    return message;
}