
#ifndef LOGGERMANAGER_H
#define LOGGERMANAGER_H

#include <Arduino.h>
#include <SD.h>

class LoggerManager {
public:
    LoggerManager(uint8_t chipSelectPin);
    bool begin();
    void log(const String &message);
    void end();

private:
    uint8_t csPin;
    File logFile;
    bool sdInitialized;
};

#endif // LOGGERMANAGER_H
