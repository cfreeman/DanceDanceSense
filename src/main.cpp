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
#include <SPI.h>
#include <Wire.h>
#include <SparkFun_ADXL345.h>

WiFiUDP Udp;
ADXL345 adxl = ADXL345();

const char* ssid = "***";           // EditThis: The name of your WiFi access point.
const char* password = "********";  // EditThis: The password of your WiFi access point.
const IPAddress dstIp(10,1,1,3);    // EditThis: The IP address of the machine to recieve OSC messages.
const unsigned int dstPort = 8000;  // EditThis: The port listening for OSC messages.
const unsigned int sensorId = 1;    // EditThis: The ID of the sensor (useful for multple sensors).

// The local listening port for UDP packets.
const unsigned int localPort = 8888;

// sendOSCData broadcasts position information over OSC to tne dst address.
void sendOSCData(float value, const char *tag) {
  OSCMessage msg(tag);
  msg.add(value);

  Udp.beginPacket(dstIp, dstPort);
  msg.send(Udp);
  Udp.endPacket();
  msg.empty();
}

// setup configures the underlying hardware for use in the main loop.
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

  adxl.powerOn();
  adxl.setRangeSetting(2);
}

// loop executes over and over on the microcontroller. Read from sensors and broadcast via OSC.
void loop() {
  int x,y,z;
  adxl.readAccel(&x, &y, &z);

  char tag[16];

  sprintf(tag, "/dds-x-%u", sensorId);
  sendOSCData((x / 512.0), tag);

  sprintf(tag, "/dds-y-%u", sensorId);
  sendOSCData((y / 512.0), tag);

  sprintf(tag, "/dds-z-%u", sensorId);
  sendOSCData((z / 512.0), tag);

  delay(250); // Sample and broadcast OSC messages four times a second.
}
