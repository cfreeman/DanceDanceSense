/*
 * Copyright (c) Clinton Freeman 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include <ESP8266Wifi.h>
#include <WiFiUdp.h>
#include <Arduino.h>
#include <OSCMessage.h>

WiFiUDP Udp;

const char* ssid = "***";
const char* password = "*********";
const unsigned int localPort = 8888;

const IPAddress dstIp(10,1,1,3);
const unsigned int dstPort = 8000;

void setup() {
  Serial.begin(9600);

  // Prevent need for powercyle after upload.
  WiFi.disconnect();

  // Use DHCP to connect and obtain IP Address.
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Wait will we have connected to the WiFi AP.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Init UDP to broadcast OSC messages.
  Udp.begin(localPort);

  Serial.println("");
  Serial.println("WiFi Connected!");
}

// sendOSCData broadcasts position information over OSC to tne dst address.
void sendOSCData(float value, char *tag) {
  OSCMessage msg(tag);
  msg.add(value);

  Udp.beginPacket(dstIp, dstPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

float v = 0.0;

void loop() {
  delay(1000);

  v = v + 0.01;

  sendOSCData(v, "dds-x");
}
