#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

// Optional SD card CS pin (can be adjusted)
const int LOGGER_SD_CS = 10;

// Tracks if the logger is present and usable
bool loggerPresent = false;

void initOptionalLoggerWing() {
  Serial.println("🔍 Checking for Logger Wing...");

  if (!SD.begin(LOGGER_SD_CS)) {
    Serial.println("⚠️ Logger Wing not found or SD not inserted.");
    loggerPresent = false;
    return;
  }

  loggerPresent = true;
  Serial.println("📝 Logger Wing initialized. SD card ready.");
}

bool loggerIsAvailable() {
  return loggerPresent;
}
