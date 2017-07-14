# DanceDanceSense

DanceDanceSense is a small wearable sensor based on an ESP8266 (NodeMCU or
similar). It sends normalised accelerometer readings via OSC messages to a host
computer.



## Compiling:

1. Install [PlatformIO for Atom](http://platformio.org/).
2. Open the DanceDanceSense project.
3. Edit the configuration at the top of src/main.cpp
4. Build the project.
5. Upload



## Hardware:

1 x ADXL345
1 x LiPo 3.7v 1200mAh
1 x ESP8266 NodeMCU
2 x 4.7kΩ Resistors.
1 x Protoboard

Hardware draws about 70mA when connected to WiFi.



## TODO:

* Add more details on hardware.



## License

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
