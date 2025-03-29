// Note: Native ICMP/ping not supported directly in Arduino Ethernet stack
// Simulate ping check by attempting DNS or TCP echo

#include <Ethernet.h>

bool pingTest(const char* host) {
  Serial.print("📡 Simulating ping to ");
  Serial.print(host);
  Serial.print("... ");
  EthernetClient client;
  if (client.connect(host, 80)) {
    Serial.println("🟢 Host reachable via TCP (port 80).");
    client.stop();
    return true;
  } else {
    Serial.println("🔴 Host unreachable.");
    return false;
  }
}
