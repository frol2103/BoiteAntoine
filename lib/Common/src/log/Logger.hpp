#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Arduino.h"

class Logger
{
private:
    bool active;

public:
    Logger(bool active){
        this->active = active;
    };

    Logger p(){
        Serial.print("");
        return this;
    }
    Logger nl(){
        Serial.println("");
        return this;
    }
};



#endif