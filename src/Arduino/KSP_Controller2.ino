#include "Config.h"
#include "USB_Handlers.h"
#include "NetworkManager.h"
#include "DisplayManager.h"
#include "InputHandler.h"
#include "CommandParser.h"

void setup() {
  initUSB();
  initDisplay();
  initNetwork();
  initInput();
  setProfile(currentProfile);
}

void loop() {
  handleInput();
  parseSerialCommands();
}
