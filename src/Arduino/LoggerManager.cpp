
#include "LoggerManager.h"

LoggerManager::LoggerManager(uint8_t chipSelectPin)
    : csPin(chipSelectPin), sdInitialized(false) {}

bool LoggerManager::begin() {
    if (!SD.begin(csPin)) {
        sdInitialized = false;
        return false;
    }
    sdInitialized = true;
    logFile = SD.open("log.txt", FILE_WRITE);
    return logFile ? true : false;
}

void LoggerManager::log(const String &message) {
    if (sdInitialized && logFile) {
        logFile.println(message);
        logFile.flush();
    }
}

void LoggerManager::end() {
    if (logFile) {
        logFile.close();
    }
}
