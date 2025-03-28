#include <KerbalSimpit.h>

KerbalSimpit simp(Serial);

void setup() {
  Serial.begin(57600);
  simp.begin();
  simp.registerChannel(0x10); // Example: Altitude
  Serial.println("Kerbal Simpit Ready.");
}

void loop() {
  simp.update();
  // Handle incoming messages here
}
