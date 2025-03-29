#include <Ethernet.h>
#include <EthernetServer.h>

EthernetServer server(80);

void startWebServer() {
  server.begin();
  Serial.println("🌐 Web server started on port 80");
}

void handleWebRequests() {
  EthernetClient client = server.available();
  if (client) {
    Serial.println("🌐 Client connected");
    bool currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html><body><h1>KSP Controller Online</h1></body></html>");
          break;
        }
        if (c == '\n') currentLineIsBlank = true;
        else if (c != '\r') currentLineIsBlank = false;
      }
    }
    delay(1);
    client.stop();
    Serial.println("🌐 Client disconnected");
  }
}
