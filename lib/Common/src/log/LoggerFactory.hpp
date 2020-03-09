#ifndef LOGGERFACTORY_HPP
#define LOGGERFACTORY_HPP

#define LOG_PERIOD (500)

#include "Arduino.h"
#include "Logger.hpp"

class LoggerFactory
{
private:
    unsigned long lastLog = 0;
public:
    Logger logger(){
        if(millis() - lastLog > LOG_PERIOD){
            lastLog=millis();
            return new Logger(true);
        } else {
            return new Logger(false);
        }
    }
};



#endif